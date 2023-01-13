# XDU HealthCard C++ Server

使用C++写的XDU HealthCard Server，个人学习使用。

## 依赖库

+ [ithewei/libhv - GitHub](https://github.com/ithewei/libhv) v1.2.6
+ [idealvin/coost - GitHub](https://github.com/idealvin/coost) v3.0.0 [文档](https://coostdocs.gitee.io/cn/about/co/)
+ [MySQL Connector/C++](https://dev.mysql.com/downloads/connector/cpp/) v8.0.25


## 使用

```bash
mkdir build && cd build
cmake ..
make
./XDU_HealthCard_Server --help # 查看帮助
```

启动程序：

```bash
./XDU_HealthCard_Server
-port=1423
-mysqlHost=127.0.0.1
-mysqlPort=3306
-mysqlUser=root
-mysqlPasswd=123456
-mysqlDB=xdu_health_card
-appID=wxe885e9927d9317a7
-secret=4025e476d05c62cbbae0cb2e04ef6d58
-mapApiKey=XHOBZ-CKERS-TNL3D-6265B-VC5AH-D7BGV
-hmacSecret=randomString
```



