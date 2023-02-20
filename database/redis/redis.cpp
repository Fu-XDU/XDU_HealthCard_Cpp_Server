//
// Created by 付铭 on 2023/2/19.
//

#include "redis.h"
#include "co/defer.h"

RedisConnPool *redisConnPool = nullptr;

bool Redis::Lock(const std::string &key) {
    return Set(key, "0", 10);
}

bool Redis::Unlock(const std::string &key) {
    return Del(key);
}

bool Redis::Del(const std::string &key) {
    if (key.empty()) {
        return false;
    }
    redisContext *conn = redisConnPool->GetConnection();
    defer(redisConnPool->ReleaseConnection(conn));
    auto *reply = (redisReply *) redisCommand(conn, "DEL %s", key.c_str());
    defer(freeReplyObject(reply));
    return reply->integer == 1;
}

bool Redis::Set(const std::string &key, const std::string &value, const int expiration = 0) {
    if (key.empty() || value.empty()) {
        return false;
    }

    redisContext *conn = redisConnPool->GetConnection();
    defer(redisConnPool->ReleaseConnection(conn));
    char * cmd = (char *) std::calloc(40, sizeof(char));
    if (expiration == 0) {
        std::sprintf(cmd, "SET %s %s NX", key.c_str(), value.c_str());
    } else {
        std::sprintf(cmd, "SET %s %s EX %d NX", key.c_str(), value.c_str(), expiration);
    }
    auto *reply = (redisReply *) redisCommand(conn, cmd);
    defer(freeReplyObject(reply));
    return strcmp(reply->str, "OK") == 0;
}