//
// Created by 付铭 on 2023/2/18.
//

#include "redis_conn_pool.h"
#include "../../utils/flag.h"
#include "co/log.h"
#include "co/defer.h"

using namespace std;

RedisConnPool *RedisConnPool::connPool = nullptr;

// 获取连接池对象，单例模式
RedisConnPool *RedisConnPool::GetInstance() {
    if (connPool == nullptr) {
        connPool = new RedisConnPool(redisHost, redisPort, redisUser, redisPasswd, redisDB, redisMaxThread,
                                     redisIdleThread);

        LOG << "Connect to redis success. IP:" << redisHost << " Port:" << redisPort;
    }

    return connPool;
}

// 数据库连接池的构造函数
RedisConnPool::RedisConnPool(string ip, int port, string userName, string password, int database, int poolSize,
                             int minIdleConns) {
    if (poolSize <= 1) {
        poolSize = 1;
    }
    if (minIdleConns > poolSize) {
        minIdleConns = poolSize;
    }
    this->poolSize = poolSize;
    this->minIdleConns = minIdleConns;
    this->curSize = 0;
    this->username = std::move(userName);
    this->password = std::move(password);
    this->ip = std::move(ip);
    this->port = port;
    this->database = database;

    // 在初始化连接池时，建立一定数量的数据库连接
    this->InitConnection(minIdleConns);
}

void RedisConnPool::InitConnection(int initialSize) {
    redisContext *conn;
    pthread_mutex_lock(&lock);

    for (int i = 0; i < initialSize; i++) {
        conn = this->CreateConnection();
        if (conn) {
            connList.push_back(conn);
            ++(this->curSize);
        } else {
            if (i == 0) {
                break;
            }
        }
    }

    FLOG_IF(this->curSize == 0) << "Connect to redis failed. IP:" << this->ip << " Port:" << this->port;

    pthread_mutex_unlock(&lock);
}

// 创建并返回一个连接
redisContext *RedisConnPool::CreateConnection() {
    redisContext *c = redisConnect(redisHost.c_str(), redisPort);
    if (c == nullptr || c->err) {
        if (c) {
            ELOG << "create connection error." << c->errstr;
        } else {
            ELOG << "Can't allocate redis context.";
        }
        redisFree(c);
        return nullptr;
    }

    auto *reply = (redisReply *) redisCommand(c, "AUTH %s", this->password.c_str());
    defer(freeReplyObject(reply));
    if (reply->type == REDIS_REPLY_ERROR) {
        ELOG << "Redis authentication failed.";
        redisFree(c);
        return nullptr;
    }
    redisEnableKeepAlive(c);
    return c;
}

// 从连接池中获得一个连接
redisContext *RedisConnPool::GetConnection() {
    redisContext *con;
    pthread_mutex_lock(&lock);

    // 连接池容器中还有连接
    if (!connList.empty()) {
        // 获取第一个连接
        con = connList.front();
        // 移除第一个连接
        connList.pop_front();
        // 判断获取到的连接的可用性
        // 如果连接已经被关闭，删除后重新建立一个
        // TODO:需验证"通过con->err来判断连接的可用性"是否有效
        if (con->err) {
            delete con;
            con = this->CreateConnection();
            // 如果连接为空，说明创建连接出错
            if (con == nullptr) {
                // 从容器中去掉这个空连接
                --curSize;
            }
        }

        pthread_mutex_unlock(&lock);
        return con;
    }
        // 连接池容器中没有连接
    else {
        // 当前已创建的连接数小于最大连接数，则创建新的连接
        if (curSize < poolSize) {
            con = this->CreateConnection();
            if (con) {
                ++curSize;
                pthread_mutex_unlock(&lock);
                return con;
            } else {
                pthread_mutex_unlock(&lock);
                return nullptr;
            }
        }
            // 当前建立的连接数已经达到最大连接数
        else {
            perror("[GetConnection] connections reach the max number.");
            pthread_mutex_unlock(&lock);
            return nullptr;
        }
    }
}

// 释放数据库连接，将该连接放回到连接池中
void RedisConnPool::ReleaseConnection(redisContext *conn) {
    if (conn) {
        pthread_mutex_lock(&lock);
        if (curSize <= minIdleConns) {
            connList.push_back(conn);
        } else {
            DestoryConnection(conn);
            curSize--;
        }
        pthread_mutex_unlock(&lock);
    }
}

// 数据库连接池的析构函数
RedisConnPool::~RedisConnPool() {
    this->DestoryConnPool();
}

// 销毁连接池，需要先销毁连接池的中连接
void RedisConnPool::DestoryConnPool() {
    list<redisContext *>::iterator itCon;
    pthread_mutex_lock(&lock);

    for (itCon = connList.begin(); itCon != connList.end(); ++itCon) {
        // 销毁连接池中的连接
        RedisConnPool::DestoryConnection(*itCon);
    }
    curSize = 0;
    // 清空连接池中的连接
    connList.clear();

    pthread_mutex_unlock(&lock);
}

// 销毁数据库连接
void RedisConnPool::DestoryConnection(redisContext *conn) {
    if (conn) {
        // 删除连接
        redisFree(conn);
        delete conn;
    }
}
