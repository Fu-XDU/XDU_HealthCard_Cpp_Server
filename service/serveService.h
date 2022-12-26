//
// Created by 付铭 on 2022/10/7.
//

#ifndef XDU_HEALTHCARD_SERVER_SERVESERVICE_H
#define XDU_HEALTHCARD_SERVER_SERVESERVICE_H


#include "../model/threeCheck.h"
#include "../model/base/retCodeDef.h"

class serveService {
public:
    static RET_CODE StorageThreeCheck(ThreeCheck *threeCheck);
};


#endif //XDU_HEALTHCARD_SERVER_SERVESERVICE_H
