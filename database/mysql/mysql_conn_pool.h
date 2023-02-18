//
// Created by 付铭 on 2022/10/8.
//

#ifndef XDU_HEALTHCARD_SERVER_MYSQL_CONN_POOL_H
#define XDU_HEALTHCARD_SERVER_MYSQL_CONN_POOL_H


#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/statement.h>
#include <pthread.h>
#include <list>
#include <string>

//using namespace std;

class MysqlConnPool {
public:
    ~MysqlConnPool();

    // 获取数据库连接
    sql::Connection *GetConnection();

    // 将数据库连接放回到连接池的容器中
    void ReleaseConnection(sql::Connection *conn);

    // 获取数据库连接池对象
    static MysqlConnPool *GetInstance();

private:
    // 当前已建立的数据库连接数量
    int curSize;
    // 连接池定义的最大数据库连接数
    int poolSize;
    // 连接池最小空闲连接数
    int minIdleConns;
    std::string username;
    std::string password;
    std::string url;
    std::string database;
    // 连接池容器
    std::list<sql::Connection *> connList;
    // 线程锁
    pthread_mutex_t lock{};
    static MysqlConnPool *connPool;
    sql::Driver *driver;

    // 创建一个连接
    sql::Connection *CreateConnection();

    // 初始化数据库连接池
    void InitConnection(int initialSize);

    // 销毁数据库连接对象
    static void DestoryConnection(sql::Connection *conn);

    // 销毁数据库连接池
    void DestoryConnPool();

    // 构造方法
    MysqlConnPool(std::string url, std::string user, std::string password, std::string database, int poolSize, int minIdleConns);

    void InitTable(std::string sql);
};


#endif //XDU_HEALTHCARD_SERVER_MYSQL_CONN_POOL_H
