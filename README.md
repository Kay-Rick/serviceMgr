# serviceMgr

> 主要封装了与服务注册中心Consul交互的部分接口，并打包成静态链接库

文件说明
- serviceInfo.h : 需要注册服务对象的描述类，作为函数的入参
- AvailableService.h : getPassingService函数出参，用于描述服务
- consulHandle.cpp : 实现与Consul交互的两个核心接口send_put和send_get
- log.c : 简易日志框架
- jsonHandle.cpp : JSON与对象相互解析的相关处理
- serviceMgr.cpp : 注册服务、获取服务相关信息的方法实现，其中tcp_server是进行健康检查与consul交互

## TODO

- 如何打包静态链接库，还未对代码进行测试