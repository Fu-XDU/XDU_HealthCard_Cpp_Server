//
// Created by 付铭 on 2022/12/26.
//

#include <iostream>
#include "co/flag.h"
#include "co/log.h"

DEF_int32(port, 8080, "Server port");
DEF_int32(threadNum, 10, "Server thread number");
DEF_string(listenHost, "0.0.0.0", "Listen host");
DEF_string(mysqlHost, "127.0.0.1", "Mysql host");
DEF_string(mysqlUser, "root", "Mysql user");
DEF_string(mysqlPasswd, "123456", "Mysql password");
DEF_string(mysqlDB, "xdu_health_card", "Mysql database name");

DEF_string(redisHost, "127.0.0.1", "Redis host");
DEF_string(redisUser, "", "Redis user");
DEF_string(redisPasswd, "123456", "Redis password");

DEF_int32(mysqlPort, 3306, "Mysql port");
DEF_int32(mysqlMaxThread, 20, "Max mysql thread count");
DEF_int32(mysqlIdleThread, 10, "Min mysql thread count");

DEF_int32(redisPort, 6379, "Redis port");
DEF_int32(redisDB, 0, "Redis db");
DEF_int32(redisMaxThread, 20, "Max redis thread count");
DEF_int32(redisIdleThread, 10, "Min redis thread count");

DEF_string(appID, "", "Appid");
DEF_string(secret, "", "App secret");
DEF_string(hmacSecret, "", "Hmac secret, a random string");
DEF_string(mapApiKey, "", "Map api key");

int port;
int threadNum;
std::string listenHost;

std::string mysqlHost;
std::string mysqlUser;
std::string mysqlPasswd;
std::string mysqlDB;

std::string redisHost;
std::string redisUser;
std::string redisPasswd;

int mysqlPort;
int mysqlMaxThread;
int mysqlIdleThread;

int redisPort;
int redisDB;
int redisMaxThread;
int redisIdleThread;

std::string appID;
std::string secret;
std::string hmacSecret;
std::string mapApiKey;

void init_env() {
    FLOG_IF(FLG_port < 0) << "wrong port: " << FLG_port;

    port = FLG_port;

    if (FLG_threadNum < 1) {
        WLOG << "threadNum cannot be set to " << FLG_threadNum << ", it is automatically set to 10";
        threadNum = 10;
    } else {
        threadNum = FLG_threadNum;
    }

    listenHost = FLG_listenHost.c_str();

    mysqlHost = FLG_mysqlHost.c_str();
    mysqlUser = FLG_mysqlUser.c_str();
    mysqlPasswd = FLG_mysqlPasswd.c_str();
    mysqlDB = FLG_mysqlDB.c_str();

    redisHost = FLG_redisHost.c_str();
    redisUser = FLG_redisUser.c_str();
    redisPasswd = FLG_redisPasswd.c_str();

    FLOG_IF(FLG_mysqlPort < 0) << "wrong mysql port: " << FLG_mysqlPort;
    mysqlPort = FLG_mysqlPort;
    mysqlMaxThread = FLG_mysqlMaxThread;
    if (FLG_mysqlMaxThread < FLG_mysqlIdleThread) {
        WLOG << "mysql idle thread: " << FLG_mysqlIdleThread << "can not be more than mysql max thread: "
             << FLG_mysqlMaxThread << ".It is automatically set to mysql max thread: " << FLG_mysqlMaxThread;
        FLG_mysqlIdleThread = mysqlMaxThread;
    }
    mysqlIdleThread = FLG_mysqlIdleThread;

    FLOG_IF(FLG_redisPort < 0) << "wrong redis port: " << FLG_redisPort;
    redisPort = FLG_redisPort;
    redisDB = FLG_redisDB;
    redisMaxThread = FLG_redisMaxThread;
    if (FLG_redisMaxThread < FLG_redisIdleThread) {
        WLOG << "redis idle thread: " << FLG_redisIdleThread << "can not be more than redis max thread: "
             << FLG_redisMaxThread << ".It is automatically set to redis max thread: " << FLG_redisMaxThread;
        FLG_redisIdleThread = FLG_redisMaxThread;
    }
    redisIdleThread = FLG_redisIdleThread;

    appID = FLG_appID.c_str();
    secret = FLG_secret.c_str();
    hmacSecret = FLG_hmacSecret.c_str();
    mapApiKey = FLG_mapApiKey.c_str();
}