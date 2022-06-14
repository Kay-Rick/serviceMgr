#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include<fstream>
#include<vector>
#include"log.h"
#include"jsonHandle.h"
using namespace std;

// 接受解析json串
string buildServiceInfoJson(ServiceInfo * serviceInfo){
    Json::Value root;
    root["ID"]=Json::Value(serviceInfo->getServiceId());
    root["Name"]=Json::Value(serviceInfo->getServiceName());
    root["Tags"].append(serviceInfo->getServiceVersion());
    root["Tags"].append(serviceInfo->getServiceProtocol());
    root["Tags"].append(serviceInfo->getServiceProvider());
    root["Address"]= Json::Value(serviceInfo->getServiceIP());
    root["Port"]=Json::Value(serviceInfo->getServicePort());
    //root["EnableTagOverride"] = Json::Value(false);
    Json::Value check;
    Json::Value weights;
    switch (serviceInfo->getCheckType())
    {
    case HTTP_CHECK:
        check["HTTP"] = Json::Value(serviceInfo->getCheckURL());
        break;
    case TCP_CHECK:
        check["TCP"] = Json::Value(serviceInfo->getCheckURL());
        break;
    default:
        break;
    }
    weights["Passing"] = Json::Value(serviceInfo->getServiceWeight());
    weights["Warning"] = Json::Value(1);
    root["Weights"] = Json::Value(weights);
    check["DeregisterCriticalServiceAfter"] = Json::Value(serviceInfo->getCheckDeregisterCriticalServiceAfter());
    check["Interval"] = Json::Value(serviceInfo->getCheckInterval());
    check["Timeout"] = Json::Value(serviceInfo->getCheckTimeout());
    check["status"] = Json::Value("passing");
    root["Check"]= Json::Value(check);

    Json::StreamWriterBuilder builder;
    //string str = Json::writeString(builder, root);
    string str = root.toStyledString();
    Log(NOTICE,"The service meta data is :\n %s\n",str.c_str());
    cout<<"json:"<<str<<endl;
    return str;
}


vector<AvailableService*> parseALLServiceInfo(string serviceJsonStr){
    Json::Reader reader;
	Json::Value root;
    vector<AvailableService*> serviceList;
	//从字符串中读取数据  
	if (reader.parse(serviceJsonStr, root))
	{
        cout<<"size:"<<root.size()<<endl;
		// for (Json::Value::ArrayIndex i = 0; i < root.size(); i++){
        //     std::string A = root[i]["ID"].asString();
        //     cout<<"id:"<<A<<endl;
        // }
        
        for (Json::Value::iterator it = root.begin(); it != root.end(); ++it) {
            string id = (*it)["ID"].asString();
            string name = (*it)["Service"].asString();
            string address = (*it)["Address"].asString();
            string port = (*it)["Port"].asString();
            string address_port = address+":"+port;
            string version,protocol,provider;
            int weight ;
            Json::Value tags = (*it)["Tags"];
            if(tags.isArray()){
                version = tags[0].asString();
                protocol = tags[1].asString();
                provider = tags[2].asString();
            }
            Json::Value weights = (*it)["Weights"];
            weight = weights["Passing"].asInt();
            AvailableService* service = new AvailableService(name,id,address_port,weight,protocol,version,provider);
            serviceList.push_back(service);
        }
	}else{
		cout << "parse error\n" << endl;
	}
    return serviceList;
}

vector<AvailableService*> parsePassingServiceInfo(string serviceJsonStr){
    Json::Reader reader;
	Json::Value root;
    vector<AvailableService*> serviceList;
	//从字符串中读取数据  
	if (reader.parse(serviceJsonStr, root))
	{
        //cout<<"debug size:"<<root.size()<<endl;
        if(root.isArray()){
            for(int i=0; i<root.size(); i++){
                Json::Value service = root[i]["Service"];
                string id = service["ID"].asString();
                string name = service["Service"].asString();
                string address = service["Address"].asString();
                string port = service["Port"].asString();
                string address_port = address+":"+port;
                string version,protocol,provider;
                int weight ;
                Json::Value tags = service["Tags"];
                if(tags.isArray()){
                    version = tags[0].asString();
                    protocol = tags[1].asString();
                    provider = tags[2].asString();
                }
                Json::Value weights = service["Weights"];
                weight = weights["Passing"].asInt();
                AvailableService* serviceItem = new AvailableService(name,id,address_port,weight,protocol,version,provider);
                serviceList.push_back(serviceItem);
            }
        }
	}else{
		cout << "parse error\n" << endl;
	}
	
    return serviceList;
}


string getServiceAddress(SERVER_NAME server_name){
    Json::Reader reader;
	Json::Value root;
 
	//从文件中读取，保证当前文件有config.json文件  
	ifstream in("config.json", ios::binary);
    string server = "";
	if (!in.is_open())
	{
        Log(ERROR,"Error opening file\n" );
	}
   
	if (reader.parse(in, root))
	{
        switch (server_name)
        {
        case  REGISTRY_CENTER:
            server = root["REGISTRY_CENTER"].asString();
            break;
        default:
            break;
        }
		
        Log(NOTICE,"The corresponding server address is %s\n",server.c_str());
	}else{
        Log(ERROR,"parse config file error %s\n",server);
		cout << "parse error\n" << endl;
	}
	in.close();
    return server;
}

string getServerIP(string serverAddress){
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

int getServerPort(string serverAddress){
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
