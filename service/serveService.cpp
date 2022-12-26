//
// Created by 付铭 on 2022/10/7.
//
#include "serveService.h"
#include "../database/connection_pool.h"
#include "../database/mysql.h"

RET_CODE serveService::StorageThreeCheck(ThreeCheck *threeCheck) {
    int success = Mysql::StorageThreeCheck(threeCheck);
    if (success) {
        std::cout << threeCheck->toString() << std::endl;
        return SUCCESS;
    } else {
        return SUCCESS;
    }
}
