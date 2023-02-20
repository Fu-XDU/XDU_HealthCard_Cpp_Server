#include "HttpServer.h"
#include "routes/router.h"
#include "co/log.h"
#include "utils/flag.h"
#include "database/mysql/mysql.h"
#include "database/redis/redis.h"
#include "./utils/utils.h"

void Run();

void startInfo(hv::HttpServer *server);

void prepare(int argc, char **argv) {
    FLG_cout = true;
    flag::init(argc, argv);
    init_env();
}

int main(int argc, char **argv) {
    prepare(argc, argv);
    mysqlConnPool = MysqlConnPool::GetInstance();
    redisConnPool = RedisConnPool::GetInstance();
    Run();
    return 0;
}

void Run() {
    hv::HttpService router;
    Router::Register(router);
    hv::HttpServer server;
    server.registerHttpService(&router);
    server.setHost(listenHost.c_str());
    server.setPort(port);
    // 服务端同时进行处理的线程数量
    // 超过这个数量的线程会被挂起，直到有线程空闲来处理它
    // 挂起的线程不会被服务端超时，可能会由客户端进行超时从而断开连接
    server.setThreadNum(threadNum);
    startInfo(&server);
    server.run();
}

void startInfo(hv::HttpServer *server) {
    Utils::printRoutes(&server->service->api_handlers);
    LOG << "Server listening on " << server->host << ":" << server->port;
}