//
// Created by 付铭 on 2022/10/7.
//
#include "serveService.h"
#include "../database/mysql/mysql.h"

RET_CODE serveService::StorageThreeCheck(ThreeCheck *threeCheck) {
    bool registered = Mysql::ThreeCheckRegistered(threeCheck->openid, threeCheck->stuID);
    if (registered) {
        return CannotSubmitAgain;
    }

    int success = Mysql::StorageThreeCheck(threeCheck);

    if (success) {
        return SUCCESS;
    } else {
        return MysqlCurdFailed;
    }
}

RET_CODE serveService::StorageHealthCard(HealthCard *healthCard) {
    // 在redis加锁

    bool registered = Mysql::HealthCardRegistered(healthCard->openid, healthCard->stuID);
    if (registered) {
        return CannotSubmitAgain;
    }

    // 查询发现没有注册
    // 准备存储时
    // 另一个线程进行了注册
    // 下面存储会出错

    int success = Mysql::StorageHealthCard(healthCard);

    // redis解锁

    if (success) {
        return SUCCESS;
    } else {
        return MysqlCurdFailed;
    }
}

RET_CODE serveService::DeleteThreeCheck(const std::string &openid) {
    bool registered = Mysql::ThreeCheckRegisteredByOpenid(openid);
    if (!registered) {
        return NotRegistered;
    }

    int success = Mysql::DeleteThreeCheck(openid);

    if (success) {
        return SUCCESS;
    } else {
        return MysqlCurdFailed;
    }
}

RET_CODE serveService::DeleteHealthCard(const std::string &openid) {
    bool registered = Mysql::HealthCardRegisteredByOpenid(openid);
    if (!registered) {
        return NotRegistered;
    }

    int success = Mysql::DeleteHealthCard(openid);

    if (success) {
        return SUCCESS;
    } else {
        return MysqlCurdFailed;
    }
}