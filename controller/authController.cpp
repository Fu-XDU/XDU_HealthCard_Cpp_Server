//
// Created by 付铭 on 2022/10/6.
//

#include "authController.h"
#include "../model/base/baseResponse.h"
#include "../utils/utils.h"

int authController::Login(HttpRequest *req, HttpResponse *resp) {
    Response response = Response::NewResponse();
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}