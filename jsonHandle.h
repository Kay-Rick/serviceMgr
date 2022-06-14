#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include<fstream>
#include<vector>
#include"serviceMgr/ServiceInfo.h"
#include"serviceMgr/AvailableService.h"
#include"serviceMgr/log.h"

enum SERVER_NAME{
    REGISTRY_CENTER
};


string getServiceAddress(SERVER_NAME server_name);
string getServerIP(string serverAddress);
int getServerPort(string serverAddress);
string buildServiceInfoJson(ServiceInfo * serviceInfo);
vector<AvailableService*> parseALLServiceInfo(string serviceJsonStr);

vector<AvailableService*> parsePassingServiceInfo(string serviceJsonStr);