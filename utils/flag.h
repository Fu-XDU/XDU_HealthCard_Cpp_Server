//
// Created by 付铭 on 2022/12/26.
//

#ifndef XDU_HEALTHCARD_SERVER_FLAG_H
#define XDU_HEALTHCARD_SERVER_FLAG_H

#include <iostream>

extern int port;
extern int threadNum;
extern std::string listenHost;

extern std::string mysqlHost;
extern std::string mysqlUser;
extern std::string mysqlPasswd;
extern std::string mysqlDB;

extern std::string redisHost;
extern std::string redisUser;
extern std::string redisPasswd;

extern int mysqlPort;
extern int mysqlMaxThread;
extern int mysqlIdleThread;

extern int redisPort;
extern int redisDB;
extern int redisMaxThread;
extern int redisIdleThread;

extern std::string appID;
extern std::string secret;
extern std::string hmacSecret;
extern std::string mapApiKey;

void init_env();

#endif //XDU_HEALTHCARD_SERVER_FLAG_H