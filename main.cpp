#include "HttpServer.h"
#include "routes/router.h"
#include "co/co.h"
#include "utils/flag.h"
#include "database/mysql.h"

void Run();

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
    server.setPort(8080);
    server.setThreadNum(4);
    server.run();
}

