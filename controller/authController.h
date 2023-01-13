//
// Created by 付铭 on 2022/10/6.
//

#ifndef XDU_HEALTHCARD_SERVER_AUTHCONTROLLER_H
#define XDU_HEALTHCARD_SERVER_AUTHCONTROLLER_H

#include "HttpService.h"

class authController {
public:
    static int Login(HttpRequest *req, HttpResponse *resp);
};


#endif //XDU_HEALTHCARD_SERVER_AUTHCONTROLLER_H
