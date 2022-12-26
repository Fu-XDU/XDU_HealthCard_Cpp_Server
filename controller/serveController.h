//
// Created by 付铭 on 2022/10/6.
//

#ifndef XDU_HEALTHCARD_SERVER_SERVECONTROLLER_H
#define XDU_HEALTHCARD_SERVER_SERVECONTROLLER_H

#include "HttpService.h"

class serveController {
public:
    static int StorageThreeCheck(HttpRequest *req, HttpResponse *resp);
};


#endif //XDU_HEALTHCARD_SERVER_SERVECONTROLLER_H
