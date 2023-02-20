//
// Created by 付铭 on 2022/10/6.
//

#include "serveController.h"
#include "../model/base/baseResponse.h"
#include "../model/threeCheck.h"
#include "../utils/utils.h"
#include "../service/serveService.h"

int serveController::GetSummary(HttpRequest *req, HttpResponse *resp) {
    Response response;
    std::string openid = req->GetParam("openid");
    Summary summary = serveService::GetSummary(openid);
    response = Response::NewResponse(summary.toJson());
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::StorageHealthCard(HttpRequest *req, HttpResponse *resp) {
    Response response;
    HealthCard healthCard;
    req->GetJson();
    try {
        healthCard.stuID = req->json["stu_id"];
        healthCard.passwd = req->json["passwd"];
        healthCard.openid = req->json["openid"];
        healthCard.location = req->json["location"];
    } catch (...) {
        response = Response::NewResponse(BindDataFailed);
        Utils::setBaseResponse(resp, &response);
        return HTTP_STATUS_OK;
    }

    RET_CODE retCode = serveService::StorageHealthCard(&healthCard);
    response = Response::NewResponse(retCode);
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::DeleteThreeCheck(HttpRequest *req, HttpResponse *resp) {
    Response response;
    std::string openid = req->GetParam("openid");
    RET_CODE retCode = serveService::DeleteThreeCheck(openid);
    response = Response::NewResponse(retCode);
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::DeleteHealthCard(HttpRequest *req, HttpResponse *resp) {
    Response response;
    std::string openid = req->GetParam("openid");
    RET_CODE retCode = serveService::DeleteHealthCard(openid);
    response = Response::NewResponse(retCode);
    Utils::setBaseResponse(resp, &response);
    return HTTP_STATUS_OK;
}

int serveController::StorageThreeCheck(HttpRequest *req, HttpResponse *resp) {
    Response response;
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
