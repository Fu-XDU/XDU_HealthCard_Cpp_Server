//
// Created by 付铭 on 2022/10/6.
//

#include "router.h"
#include "HttpServer.h"
#include "../controller/serveController.h"
#include "../controller/authController.h"

void Router::Register(hv::HttpService &router) {
    router.GET("/v1/serve/summary", serveController::GetSummary);
    router.POST("/v1/serve/three-check", serveController::StorageThreeCheck);
    router.POST("/v1/serve/health-card", serveController::StorageHealthCard);
    router.Delete("/v1/serve/three-check", serveController::DeleteThreeCheck);
    router.Delete("/v1/serve/health-card", serveController::DeleteHealthCard);
    router.POST("/v1/auth/login", authController::Login);
}