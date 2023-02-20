//
// Created by 付铭 on 2023/2/20.
//

#ifndef XDU_HEALTHCARD_SERVER_SUMMARY_H
#define XDU_HEALTHCARD_SERVER_SUMMARY_H

#include "./threeCheck.h"
#include "./healthCard.h"
#include <json.hpp>

struct Summary {
    ThreeCheck threeCheck;
    HealthCard healthCard;

    nlohmann::json toJson() {
        nlohmann::json json = {
                {"three_check", this->threeCheck.toJson()},
                {"health_card", this->healthCard.toJson()}
        };
        return json;
    }
};

#endif //XDU_HEALTHCARD_SERVER_SUMMARY_H
