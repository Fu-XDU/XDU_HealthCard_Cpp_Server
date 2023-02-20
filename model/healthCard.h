//
// Created by 付铭 on 2022/10/6.
//

#ifndef XDU_HEALTHCARD_SERVER_HEALTHCARD_H
#define XDU_HEALTHCARD_SERVER_HEALTHCARD_H

#include "iostream"
#include <json.hpp>

struct HealthCard {
    int id;
    std::string openid;
    std::string stuID;
    std::string passwd;
    std::string location;

    [[nodiscard]] std::string toString() const {
        return "stuID:" + this->stuID;
    }

    nlohmann::json toJson() {
        nlohmann::json json = {
                {"id",       this->id},
                {"openid",   this->openid},
                {"stu_id",   this->stuID},
                {"passwd",   this->passwd},
                {"location", this->location},
        };
        return json;
    }
};

#endif //XDU_HEALTHCARD_SERVER_HEALTHCARD_H
