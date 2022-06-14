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
using namespace std;
    string send_put(const string& url,char * para);
    string send_get(const string& url);