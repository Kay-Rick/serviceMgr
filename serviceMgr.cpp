#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
#include <jsoncpp/json/json.h>
#include <iconv.h>
#include <iostream>
#include <sstream>
#include "consulHandle.h"
#include"serviceMgr.h"
#include<ctime>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include <cstdlib>
#include<string>
#define MAXLINE 4096


using namespace std;
string consulServer;
void * tcp_server(void * portAddress){
    int  listenfd, connfd;
    struct sockaddr_in  servaddr;
    char  buff[4096];
    int  n;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        Log(ERROR,"create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    int * port_pointer =  (int *)portAddress;
    int port = *port_pointer;
    delete port_pointer;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        Log(ERROR,"tcp health check bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    if( listen(listenfd, 10) == -1){
        Log(ERROR,"tcp health check listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    printf("======port %d waiting for client's request======\n",port);
    Log(NOTICE,"======port %d waiting for client's request======\n",port );
    int randNum;
    while(1){
        if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
            Log(ERROR,"accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        randNum = rand()%10;
        if(randNum >7) {//日志输出太多了，通过随机数只输出1/5的
            Log(NOTICE,"received health check from register center\n");
        }        
        close(connfd);
    }
    close(listenfd);
    return 0;
}

 //得到一个0-10000的随机数
int getRandom(){   
    srand((int)time(0));// 产生随机种子  把0换成NULL也行
    int randomNum = rand() % 10000;  
    return randomNum;
}


//注册服务
int registerService(ServiceInfo * serviceInfo){
    if(consulServer.empty()){
         consulServer = getServiceAddress(REGISTRY_CENTER);
    }
    string url = "http://"+consulServer+"/v1/agent/service/register";   
    string randomNum = to_string(getRandom());
    string serviceId = serviceInfo->getServiceName()+randomNum;
    serviceInfo->setServiceId(serviceId);
    //attention! start health check first and then register service
    
    //tcp health check
    string checkURL = serviceInfo->getCheckURL();
    int * checkPort = new int;
    *checkPort = getServerPort(checkURL);
    Log(NOTICE,"The checkURL is %s\n",checkURL.c_str());
    if(TCP_CHECK==serviceInfo->getCheckType()){
        int * thread_res = NULL;
        pthread_t th;
        int ret = pthread_create(&th, NULL, tcp_server,checkPort);
    }
    //sleep(3);//先开启健康检查接口，再注册服务，不然注册完服务后会有短暂的服务异常状态，影响服务监控检查程序的运行。
    string jsonStr = buildServiceInfoJson(serviceInfo);
    char param[500] = {0};
    strcpy(param, jsonStr.c_str());
	string registerRes = send_put(url, param);
    string flag = "200 OK";
     // 子串位于字符串中的位置
    size_t nLoc = registerRes.find(flag);
    // 如果检索到子串在字符串中，则打印子串的位置
    if (nLoc == string::npos)
    {
        Log(ERROR,"Register service fail, response is %s\n",registerRes.c_str());
        return 1;
    }
    printf("Register service %s successfully! \n",serviceId.c_str());
    Log(NOTICE,"Register service %s successfully! \n",serviceId.c_str());
    return 0;
 } 


vector<AvailableService*> getAllService(){
    if(consulServer.empty()){
         consulServer = getServiceAddress(REGISTRY_CENTER);
    }
    string url =  "http://"+consulServer+"/v1/agent/services";
    string servicesJsonStr = send_get(url);
    vector<AvailableService *> serviceList = parsePassingServiceInfo(servicesJsonStr);
    return serviceList;
}

vector<AvailableService*> getPassingService(const string& serviceName ){
    //cout<<"debug: serviceName:"<<serviceName<<endl;
    if(consulServer.empty()){
         consulServer = getServiceAddress(REGISTRY_CENTER);
    }
    string url =  "http://"+consulServer+"/v1/health/service/"+serviceName+"?passing";
    Log(NOTICE,"The url to get services is :%s\n",url.c_str());
    //cout<<"debug: url:"<<url<<endl;
    string servicesJsonStr = send_get(url);
    vector<AvailableService*> serviceList = parsePassingServiceInfo(servicesJsonStr);
    Log(NOTICE,"The size of available service list is %d\n",serviceList.size());
    return serviceList;
}


map<string, int> getServerList(const string& serviceName ){
    vector<AvailableService*> list = getPassingService(serviceName);
    map<string, int> servicesMap;
    if(!list.empty()){
        for (int i = 0; i < list.size(); i++)
        {
            servicesMap.insert(pair<string, int>(list[i]->getServiceAddress(),list[i]->getserviceWeight()));
        }
        
    }
    return servicesMap;
}


string getSelectedServer(const string& serviceName){
    map<string, int> servicesMap = getServerList(serviceName);
    int count = servicesMap.size();
    string server;
    //如果服务数量为0，直接返回
    if(count ==0){
        Log(ERROR,"The selected server amount is 0!\n");
        return server;
    }
    map<string,int>::iterator iter;
    int weightSum = 0; 
    for(iter = servicesMap.begin(); iter != servicesMap.end(); iter++)  {
        weightSum = weightSum+iter->second;
    }
    //如果权重为0，直接返回
    if(weightSum==0){
        Log(ERROR,"The selected server weightSum is 0!\n");
        return server;
    }
    int selectedRand = rand()%(weightSum)+1;
    int sum = 0;
    
    for(iter = servicesMap.begin(); iter != servicesMap.end(); iter++)  {
        sum = sum +iter->second;
        if(sum == selectedRand || sum >selectedRand){
            server = iter->first;
            break;
        }
    }
    return server;
}

string getSelectedServerIP(string serverAddress){
    string server = "";
    if(serverAddress.empty()){
        Log(ERROR,"Server address is null\n");
       return server;
    }
    string delim = ":";
    size_t pos = serverAddress.find(delim);
    string address, port;
    if (pos == string::npos)
    {
        Log(ERROR,"Server address does not contain delimeter\n");
        return server;
    }
    address = serverAddress.substr(0,pos);
   return address;
}

int getSelectedServerPort(string serverAddress){
    int port = -1;
    if(serverAddress.empty()){
        Log(ERROR,"Server address is null\n");
        return port;
    }
    string delim = ":";
    size_t pos = serverAddress.find(delim);
    if (pos == string::npos)
    {
        Log(ERROR,"Server address does not contain delimeter\n");
        return 1;
    }
    size_t start = pos+1;
    port = atoi( serverAddress.substr(start).c_str());
    return port;

}

