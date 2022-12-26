//
// Created by 付铭 on 2022/10/6.
//

#include "router.h"
#include "HttpServer.h"
#include "../controller/serveController.h"

void Router::Register(hv::HttpService &router) {
    router.POST("/serve", serveController::StorageThreeCheck);
}