//
// Created by 付铭 on 2022/10/6.
//

#include "HttpServer.h"
#include "../model/base/baseResponse.h"
#include "utils.h"

void Utils::setBaseResponse(HttpResponse *resp, Response *response) {
    resp->json["code"] = response->code;
    resp->json["message"] = response->message;
    resp->json["success"] = response->success;
    resp->json["error"] = response->error;
    resp->json["data"] = response->data;
}
