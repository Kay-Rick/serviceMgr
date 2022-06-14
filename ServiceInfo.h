#include<string>
#include <stdio.h>
#include<iostream>
using std::string;
/*health check type*/
#define	HTTP_CHECK 1 /*http+interval*/
#define	TCP_CHECK 2  /*tcp+interval*/
class ServiceInfo {
    string serviceName;
    string serviceId;    
    string serviceIP;//服务ip
    int servicePort;    
    string serviceProtocol;
    string serviceVersion;    
    string serviceProvider;
    int serviceWeight;
    int checkType;
    string checkURL;
    string checkDeregisterCriticalServiceAfter;
    string checkInterval;
    string checkTimeout;

    public:

    ServiceInfo() {
    }

     ServiceInfo(string serviceName, string serviceId, string serviceIP, int servicePort, string serviceProtocol, string serviceVersion, string serviceProvider,int serviceWeight, int checkType, string checkURL, string checkInterval,string checkDeregisterCriticalServiceAfter, string checkTimeout) {
        this->serviceName = serviceName;
        this->serviceId = serviceId;
        this->serviceIP = serviceIP;
        this->servicePort = servicePort;
        this->serviceProtocol = serviceProtocol;
        this->serviceVersion = serviceVersion;
        this->serviceProvider = serviceProvider;
        this->serviceWeight =  serviceWeight;
        this->checkType = checkType;
        this->checkURL = checkURL;
        this->checkInterval = checkInterval;
        this->checkDeregisterCriticalServiceAfter = checkDeregisterCriticalServiceAfter;
        this->checkTimeout = checkTimeout;
    }

     string getServiceName() {
        return serviceName;
    }

     void setServiceName(string serviceName) {
        this->serviceName = serviceName;
    }

     string getServiceId() {
        return serviceId;
    }

     void setServiceId(string serviceId) {
        this->serviceId = serviceId;
    }

     string getServiceIP() {
        return serviceIP;
    }

     void setServiceIP(string serviceIP) {
        this->serviceIP = serviceIP;
    }

     int getServicePort() {
        return servicePort;
    }

     void setServicePort(int servicePort) {
        this->servicePort = servicePort;
    }

     string getServiceProtocol() {
        return serviceProtocol;
    }

     void setServiceProtocol(string serviceProtocol) {
        this->serviceProtocol = serviceProtocol;
    }

     string getServiceVersion() {
        return serviceVersion;
    }

     void setServiceVersion(string serviceVersion) {
        this->serviceVersion = serviceVersion;
    }

     string getServiceProvider() {
        return serviceProvider;
    }

     void setServiceProvider(string serviceProvider) {
        this->serviceProvider = serviceProvider;
    }

     int getServiceWeight() {
        return serviceWeight;
    }

     void setServiceWeight(int serviceWeight) {
        this->serviceWeight = serviceWeight;
    }

     int getCheckType() {
        return checkType;
    }

     void setCheckType(int checkType) {
        this->checkType = checkType;
    }

     string getCheckURL() {
        return checkURL;
    }

     void setCheckURL(string checkURL) {
        this->checkURL = checkURL;
    }

     string getCheckInterval() {
        return checkInterval;
    }

     void setCheckInterval(string checkInterval) {
        this->checkInterval = checkInterval;
    }

    string getCheckTimeout() {
        return checkTimeout;
    }

     void setCheckTimeout(string checkTimeout) {
        this->checkTimeout = checkTimeout;
    }

     string getCheckDeregisterCriticalServiceAfter() {
        return checkDeregisterCriticalServiceAfter;
    }

     void setCheckDeregisterCriticalServiceAfter(string checkDeregisterCriticalServiceAfter) {
        this->checkDeregisterCriticalServiceAfter = checkDeregisterCriticalServiceAfter;
    }

};