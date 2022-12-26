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
};

#endif //XDU_HEALTHCARD_SERVER_UTILS_H
