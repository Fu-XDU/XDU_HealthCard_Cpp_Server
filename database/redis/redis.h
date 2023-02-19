//
// Created by 付铭 on 2023/2/19.
//

#ifndef XDU_HEALTHCARD_SERVER_REDIS_H
#define XDU_HEALTHCARD_SERVER_REDIS_H

#include "redis_conn_pool.h"

extern RedisConnPool *redisConnPool;

class Redis {
public:
    static bool Lock(const std::string &key);

    static bool Del(const std::string &key);

    static bool Set(const std::string &key, const std::string &value, int expiration);

    static bool Unlock(const std::string &key);
};


#endif //XDU_HEALTHCARD_SERVER_REDIS_H
