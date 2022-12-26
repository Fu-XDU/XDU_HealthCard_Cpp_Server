//
// Created by 付铭 on 2022/10/6.
//

#ifndef XDU_HEALTHCARD_SERVER_BASERESPONSE_H
#define XDU_HEALTHCARD_SERVER_BASERESPONSE_H

#include <string>
#include <json.hpp>
#include "retCodeDef.h"

class Response {
public:
    int code{};
    std::string message;
    bool success{};
    std::string error;
    nlohmann::json data;

    static Response NewResponse(nlohmann::json data) {
        Response response = NewResponse(SUCCESS);
        response.data = std::move(data);
        return response;
    }

    static Response NewResponse() {
        return NewResponse(SUCCESS);
    }

    static Response NewResponse(const RET_CODE &retCode) {
        Response response;
        response.code = retCode.code;
        response.message = retCode.message;
        response.success = retCode.code == 0;
        response.error = "";
        response.data = "";
        return response;
    }
};


#endif //XDU_HEALTHCARD_SERVER_BASERESPONSE_H
