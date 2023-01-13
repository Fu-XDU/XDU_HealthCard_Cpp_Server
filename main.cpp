#include "HttpServer.h"
#include "routes/router.h"
#include "co/log.h"
#include "utils/flag.h"
#include "database/mysql.h"
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
    connPool = ConnPool::GetInstance();
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
    server.setThreadNum(4);
    startInfo(&server);
    server.run();
}

void startInfo(hv::HttpServer *server) {
    Utils::printRoutes(&server->service->api_handlers);
    LOG << "Server listening on " << server->host << ":" << server->port;
}