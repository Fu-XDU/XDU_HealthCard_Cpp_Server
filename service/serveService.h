//
// Created by 付铭 on 2022/10/7.
//

#ifndef XDU_HEALTHCARD_SERVER_SERVESERVICE_H
#define XDU_HEALTHCARD_SERVER_SERVESERVICE_H


#include "../model/threeCheck.h"
#include "../model/healthCard.h"
#include "../model/base/retCodeDef.h"

class serveService {
public:
    static RET_CODE StorageThreeCheck(ThreeCheck *threeCheck);

    static RET_CODE StorageHealthCard(HealthCard *healthCard);

    static RET_CODE DeleteThreeCheck(const std::string &openid);

    static RET_CODE DeleteHealthCard(const std::string &openid);
};


#endif //XDU_HEALTHCARD_SERVER_SERVESERVICE_H
