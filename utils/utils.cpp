//
// Created by 付铭 on 2022/10/6.
//

#include "HttpServer.h"
#include "../model/base/baseResponse.h"
#include "utils.h"
#include "co/log.h"

void Utils::setBaseResponse(HttpResponse *resp, Response *response) {
    resp->json["code"] = response->code;
    resp->json["message"] = response->message;
    resp->json["success"] = response->success;
    resp->json["error"] = response->error;
    resp->json["data"] = response->data;
}

void Utils::printRoutes(http_api_handlers *http_api_handlers) {
    for (const auto &item: *http_api_handlers) {
        for (const auto &second: *item.second) {
            const char *c = http_method_str(second.method);
            LOG << c << Utils::widthBlank(6 - strlen(c)) << " " << item.first.c_str();
        }
    }
}

std::string Utils::widthBlank(int width) {
    std::string s;
    for (int i = 0; i < width; i++) {
        s.append(" ");
    }
    return s;
}