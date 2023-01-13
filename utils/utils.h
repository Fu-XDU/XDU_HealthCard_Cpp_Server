//
// Created by 付铭 on 2022/10/6.
//

#ifndef XDU_HEALTHCARD_SERVER_UTILS_H
#define XDU_HEALTHCARD_SERVER_UTILS_H

#include "HttpServer.h"
#include "../model/base/baseResponse.h"

class Utils {
public:
    static void setBaseResponse(HttpResponse *resp, Response *response);

    static void printRoutes(http_api_handlers *http_api_handlers);

    static std::string widthBlank(int width);
};

#endif //XDU_HEALTHCARD_SERVER_UTILS_H
