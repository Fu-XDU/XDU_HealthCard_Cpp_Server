//
// Created by 付铭 on 2022/12/26.
//

#ifndef XDU_HEALTHCARD_SERVER_FLAG_H
#define XDU_HEALTHCARD_SERVER_FLAG_H

#include <iostream>

extern int port;
extern std::string mysqlHost;
extern std::string mysqlUser;
extern std::string mysqlPasswd;
extern std::string mysqlDB;
extern int mysqlPort;
extern int mysqlMaxThread;
extern int mysqlIdleThread;

extern std::string appID;
extern std::string secret;
extern std::string hmacSecret;
extern std::string mapApiKey;

void init_env();

#endif //XDU_HEALTHCARD_SERVER_FLAG_H