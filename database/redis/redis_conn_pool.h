//
// Created by 付铭 on 2023/2/18.
//

#ifndef XDU_HEALTHCARD_SERVER_REDIS_CONN_POOL_H
#define XDU_HEALTHCARD_SERVER_REDIS_CONN_POOL_H

#include "hiredis/hiredis.h"
#include <list>
#include <string>

class RedisConnPool {
public:
    ~RedisConnPool();

    // 获取数据库连接
    redisContext *GetConnection();

    // 将数据库连接放回到连接池的容器中
    void ReleaseConnection(redisContext *conn);

    // 获取数据库连接池对象
    static RedisConnPool *GetInstance();

private:
    std::string ip;
    int port;
    std::string username;
    std::string password;
    int database;

    // 当前已建立的数据库连接数量
    int curSize;
    // 连接池定义的最大数据库连接数
    int poolSize;
    // 连接池最小空闲连接数
    int minIdleConns;

    // 连接池容器
    std::list<redisContext *> connList;
    // 线程锁
    pthread_mutex_t lock{};
    static RedisConnPool *connPool;

    // 创建一个连接
    redisContext *CreateConnection();

    // 初始化数据库连接池
    void InitConnection(int initialSize);

    // 销毁数据库连接对象
    static void DestoryConnection(redisContext *conn);

    // 销毁数据库连接池
    void DestoryConnPool();

    // 构造方法
    RedisConnPool(std::string ip, int port, std::string user, std::string password, int database, int poolSize,
                  int minIdleConns);
};


#endif //XDU_HEALTHCARD_SERVER_REDIS_CONN_POOL_H
