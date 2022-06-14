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
#include"serviceMgr/consulHandle.h"
using namespace std;
// 与Consul交互的接口
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    string data((const char*) ptr, (size_t) size * nmemb);

    *((stringstream*) stream) << data << endl;

    return size * nmemb;
}
 
string send_put(const string& url,char * para)
{
    std::stringstream res_str;
	CURL *curl = NULL;
	CURLcode curl_res;
	curl_global_init(CURL_GLOBAL_ALL);
    
    curl = curl_easy_init();
    struct curl_slist *headers = NULL;
	if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(para));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, para);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &res_str);
        curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
        
        headers = curl_slist_append(headers,"Content-Type: application/json;charset=utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_res = curl_easy_perform(curl);

        if(curl_res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(curl_res));
        }
        curl_easy_cleanup(curl);
	}
    curl_global_cleanup();
    curl_slist_free_all(headers);
	string str_json = res_str.str();
	// char *str;
    // str = (char *)malloc(200);
    // strcpy(str, str_json.c_str());
    return str_json;
}

string  send_get(const string& url)
{
    CURL *curl;
    CURLcode res;
    string fileName ="/home/hanxi/hx_project/registryClient/info/get";
   
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: Agent-007");
    curl = curl_easy_init();    // 初始化
    string str_json ;
    std::stringstream out;
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);// 改协议头
        curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
        
        
        //注册回调函数，获取信息
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,&out); //将返回的数据输出到字符串
     
        res = curl_easy_perform(curl);   // 执行
        if (res != 0) {
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        // 接受数据存放在out中，输出之
        string str_json = out.str();
        return str_json;
    }
    return str_json;
}