//
// Created by 付铭 on 2022/10/6.
//

#ifndef XDU_HEALTHCARD_SERVER_ROUTER_H
#define XDU_HEALTHCARD_SERVER_ROUTER_H

#include "HttpServer.h"

class Router {
public:
    static void Register(hv::HttpService &router);
};


#endif //XDU_HEALTHCARD_SERVER_ROUTER_H
