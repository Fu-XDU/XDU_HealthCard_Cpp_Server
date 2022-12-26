//
// Created by 付铭 on 2022/10/8.
//

#include <stdexcept>
#include <exception>
#include <utility>
#include "connection_pool.h"
#include "co/log.h"
#include "../utils/flag.h"

using namespace std;

ConnPool *ConnPool::connPool = nullptr;

// 获取连接池对象，单例模式
ConnPool *ConnPool::GetInstance() {
    if (connPool == nullptr) {
        string url = "tcp://" + mysqlHost + ":" + std::to_string(mysqlPort);
        connPool = new ConnPool(url, mysqlUser, mysqlPasswd, mysqlMaxThread,
                                mysqlIdleThread);

        LOG << "Connect to mysql success. Url:" + url;
    }

    return connPool;
}

// 数据库连接池的构造函数
ConnPool::ConnPool(string url, string userName, string password, int poolSize, int minIdleConns) {
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
    this->url = std::move(url);

    try {
        this->driver = sql::mysql::get_driver_instance();
    }
    catch (sql::SQLException &e) {
        ELOG << "get driver error.";
    }
    catch (std::runtime_error &e) {
        ELOG << "[ConnPool] run time error.";
    }

    // 在初始化连接池时，建立一定数量的数据库连接
    this->InitConnection(minIdleConns);
}

// 初始化数据库连接池，创建最大连接数一半的连接数量
void ConnPool::InitConnection(int initialSize) {
    sql::Connection *conn;
    pthread_mutex_lock(&lock);

    for (int i = 0; i < initialSize; i++) {
        conn = this->CreateConnection();
        if (conn) {
            connList.push_back(conn);
            ++(this->curSize);
        } else {
            ELOG << "Init connection error.";
        }
    }

    FLOG_IF(this->curSize == 0) << "Connect to mysql failed. Url:" + this->url;

    pthread_mutex_unlock(&lock);
}

// 创建并返回一个连接
sql::Connection *ConnPool::CreateConnection() {
    sql::Connection *conn;
    try {
        // 建立连接
        conn = driver->connect(this->url, this->username, this->password);
        return conn;
    }
    catch (sql::SQLException &e) {
        ELOG << "create connection error.";
        return nullptr;
    }
    catch (std::runtime_error &e) {
        ELOG << "[CreateConnection] run time error.";
        return nullptr;
    }
}

// 从连接池中获得一个连接
sql::Connection *ConnPool::GetConnection() {
    sql::Connection *con;
    pthread_mutex_lock(&lock);

    // 连接池容器中还有连接
    if (!connList.empty()) {
        // 获取第一个连接
        con = connList.front();
        // 移除第一个连接
        connList.pop_front();
        // 判断获取到的连接的可用性
        // 如果连接已经被关闭，删除后重新建立一个
        if (con->isClosed()) {
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
void ConnPool::ReleaseConnection(sql::Connection *conn) {
    if (conn) {
        pthread_mutex_lock(&lock);
        std::cout << curSize << " " << minIdleConns << std::endl;
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
ConnPool::~ConnPool() {
    this->DestoryConnPool();
}

// 销毁连接池，需要先销毁连接池的中连接
void ConnPool::DestoryConnPool() {
    list<sql::Connection *>::iterator itCon;
    pthread_mutex_lock(&lock);

    for (itCon = connList.begin(); itCon != connList.end(); ++itCon) {
        // 销毁连接池中的连接
        ConnPool::DestoryConnection(*itCon);
    }
    curSize = 0;
    // 清空连接池中的连接
    connList.clear();

    pthread_mutex_unlock(&lock);
}

// 销毁数据库连接
void ConnPool::DestoryConnection(sql::Connection *conn) {
    if (conn) {
        try {
            conn->close();
            LOG << "关闭conn";
        }
        catch (sql::SQLException &e) {
            perror(e.what());
        }
        catch (std::exception &e) {
            perror(e.what());
        }
        // 删除连接
        delete conn;
    }
}



