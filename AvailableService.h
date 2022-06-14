#include<string>
#include <stdio.h>
#include<iostream>
using namespace std;

class AvailableService {
    
    string serviceName;
    string serviceId;
    string serviceAddress;
    string serviceProtocol;
    string serviceVersion;
    string serviceProvider;
    int serviceWeight;

    
    public :
    
    string getServiceName() {
        return serviceName;
    }

    void setServiceName(
        string serviceName) {
        this->serviceName = serviceName;
    }

    
    string getServiceId() {
        return serviceId;
    }

     void setServiceId(
        string serviceId) {
        this->serviceId = serviceId;
    }

     
    string getServiceAddress() {
        return serviceAddress;
    }

   void setServiceAddress(
        string serviceAddress) {
        this->serviceAddress = serviceAddress;
    }

     int getserviceWeight() {
        return serviceWeight;
    }

     void setserviceWeight(int serviceWeight) {
        this->serviceWeight = serviceWeight;
    }

     
    string getServiceProtocol() {
        return serviceProtocol;
    }

     void setServiceProtocol(
        string serviceProtocol) {
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

    void setServiceProvider(
        string serviceProvider) {
        this->serviceProvider = serviceProvider;
    }

    AvailableService(string serviceName, string serviceId, string serviceAddress, int serviceWeight, 
        string serviceProtocol, string serviceVersion, string serviceProvider) {
        this->serviceName = serviceName;
        this->serviceId = serviceId;
        this->serviceAddress = serviceAddress;
        this->serviceWeight = serviceWeight;
        this->serviceProtocol = serviceProtocol;
        this->serviceVersion = serviceVersion;
        this->serviceProvider = serviceProvider;
    }
    AvailableService(){

    }

    void printService(){
        cout<<"---------------service info-------------------";
        cout<<"service id: "<<this->serviceId<<endl;
        cout<<"service name: "<<this->serviceName<<endl;
        cout<<"service url: "<<this->serviceAddress<<endl;
        cout<<"service version: "<<this->serviceVersion<<endl;
        cout<<"service protocol: "<<this->serviceProtocol<<endl;
        cout<<"service provider: "<<this->serviceProvider<<endl;
        cout<<"service weight: "<<this->serviceWeight<<endl;
    }

};
