//
// Created by 付铭 on 2022/10/6.
//

#include "serveController.h"
#include "../model/base/baseResponse.h"
#include "../model/threeCheck.h"
#include "../utils/utils.h"
#include "../service/serveService.h"

int serveController::GetSummary(HttpRequest *req, HttpResponse *resp) {
    Response response = Response::NewResponse();
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::StorageHealthCard(HttpRequest *req, HttpResponse *resp) {
    Response response = Response::NewResponse();
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::DeleteThreeCheck(HttpRequest *req, HttpResponse *resp) {
    Response response = Response::NewResponse();
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::DeleteHealthCard(HttpRequest *req, HttpResponse *resp) {
    Response response = Response::NewResponse();
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::StorageThreeCheck(HttpRequest *req, HttpResponse *resp) {
    Response response = Response::NewResponse();
    ThreeCheck threeCheck;
    req->GetJson();
    try {
        threeCheck.stuID = req->json["stu_id"];
        threeCheck.passwd = req->json["passwd"];
        threeCheck.openid = req->json["openid"];
        threeCheck.location = req->json["location"];
    } catch (...) {
        response = Response::NewResponse(BindDataFailed);
        Utils::setBaseResponse(resp, &response);
        return HTTP_STATUS_OK;
    }

    RET_CODE retCode = serveService::StorageThreeCheck(&threeCheck);
    response = Response::NewResponse(retCode);
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}
