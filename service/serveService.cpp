//
// Created by 付铭 on 2022/10/7.
//
#include <co/defer.h>
#include "serveService.h"
#include "../database/mysql/mysql.h"
#include "../database/redis/redis.h"

Summary serveService::GetSummary(const std::string &openid) {
    Summary summary;
    summary.threeCheck = Mysql::GetNeededThreeCheckByOpenid(openid);
    summary.healthCard = Mysql::GetNeededHealthCardByOpenid(openid);
    return summary;
}

RET_CODE serveService::StorageThreeCheck(ThreeCheck *threeCheck) {
    // 在redis加锁，保证多线程安全
    std::string lockKey = "StorageThreeCheck_" + threeCheck->openid;
    bool lockSuccess = Redis::Lock(lockKey);
    if (!lockSuccess) {
        return LockExist;
    }
    defer(Redis::Unlock(lockKey));

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
    // 查询发现没有注册，那么在准备存储时，如果另一个线程也查询发现没有注册，也会进行注册
    // 应避免多个线程同时注册情况的发生
    // 所以需要在redis加锁
    std::string lockKey = "StorageHealthCard_" + healthCard->openid;
    bool lockSuccess = Redis::Lock(lockKey);
    if (!lockSuccess) {
        return LockExist;
    }
    defer(Redis::Unlock(lockKey));

    bool registered = Mysql::HealthCardRegistered(healthCard->openid, healthCard->stuID);
    if (registered) {
        return CannotSubmitAgain;
    }

    int success = Mysql::StorageHealthCard(healthCard);

    if (success) {
        return SUCCESS;
    } else {
        return MysqlCurdFailed;
    }
}

RET_CODE serveService::DeleteThreeCheck(const std::string &openid) {
    // 在redis加锁，保证多线程安全
    std::string lockKey = "DeleteThreeCheck_" + openid;
    bool lockSuccess = Redis::Lock(lockKey);
    if (!lockSuccess) {
        return LockExist;
    }
    defer(Redis::Unlock(lockKey));

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
    // 在redis加锁，保证多线程安全
    std::string lockKey = "DeleteHealthCard_" + openid;
    bool lockSuccess = Redis::Lock(lockKey);
    if (!lockSuccess) {
        return LockExist;
    }
    defer(Redis::Unlock(lockKey));

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