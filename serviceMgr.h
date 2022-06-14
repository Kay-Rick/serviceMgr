#ifndef __SERVICEMGR_H
#define __SERVICEMGR_H
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
#include<thread>
#include"serviceMgr/jsonHandle.h"


using namespace std;
    /**
     * @brief register a service
     * 
     * @param serviceInfo 
     * @return int 
     */
    int registerService(ServiceInfo * serviceInfo);
    /**
     * @brief Get the Passing Service object
     * 
     * @param serviceName 
     * @return vector<AvailableService*> 
     */
    vector<AvailableService*> getPassingService(const string& serviceName);
    /**
     * @brief Get the All Service object
     * 
     * @return vector<AvailableService*> 
     */
    vector<AvailableService*> getAllService();
    map<string, int> getServerList(const string& serviceName);
    /**
     * @brief Get the Selected Server object,
     * 
     * @param serviceName 
     * @return string 
     */
    string getSelectedServer(const string& serviceName);

    /**
     * @brief Get the Selected Server IP object
     * 
     * @param serverAddress 
     * @return string 
     */
    string getSelectedServerIP(string serverAddress);

    /**
     * @brief Get the Selected Server Port object
     * 
     * @param serverAddress 
     * @return int 
     */
    int getSelectedServerPort(string serverAddress);

#endif