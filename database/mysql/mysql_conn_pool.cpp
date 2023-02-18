//
// Created by 付铭 on 2022/10/8.
//

#include "mysql_conn_pool.h"
#include "co/log.h"
#include "../../utils/flag.h"
#include "co/defer.h"

using namespace std;

MysqlConnPool *MysqlConnPool::connPool = nullptr;

// 获取连接池对象，单例模式
MysqlConnPool *MysqlConnPool::GetInstance() {
    if (connPool == nullptr) {
        string url = "tcp://" + mysqlHost + ":" + std::to_string(mysqlPort);
        connPool = new MysqlConnPool(url, mysqlUser, mysqlPasswd, mysqlDB, mysqlMaxThread,
                                     mysqlIdleThread);

        LOG << "Connect to mysql success. Url:" + url;
    }

    return connPool;
}

// 数据库连接池的构造函数
MysqlConnPool::MysqlConnPool(string url, string userName, string password, string database, int poolSize, int minIdleConns) {
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
    this->database = std::move(database);

    try {
        this->driver = sql::mysql::get_driver_instance();
    }
    catch (sql::SQLException &e) {
        ELOG << "get driver error." << e.what();
    }
    catch (std::runtime_error &e) {
        ELOG << "[MysqlConnPool] run time error." << e.what();
    }

    // 在初始化连接池时，建立一定数量的数据库连接
    this->InitConnection(minIdleConns);

    this->InitTable("");
}

void MysqlConnPool::InitTable(std::string sql) {
    sql = R"(CREATE TABLE IF NOT EXISTS `health_cards` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `openid` varchar(40) DEFAULT NULL,
  `stu_id` varchar(20) DEFAULT NULL,
  `passwd` longtext,
  `location` varchar(1023) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_health_cards_openid` (`openid`),
  UNIQUE KEY `idx_health_cards_stu_id` (`stu_id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;)";

    sql::Connection *conn = this->GetConnection();
    defer(this->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement(sql);
    defer(delete pstmt);
    pstmt->executeUpdate();

}

// 初始化数据库连接池
void MysqlConnPool::InitConnection(int initialSize) {
    sql::Connection *conn;
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

    FLOG_IF(this->curSize == 0) << "Connect to mysql failed. Url:" << this->url << " Database:" << this->database;

    pthread_mutex_unlock(&lock);
}

// 创建并返回一个连接
sql::Connection *MysqlConnPool::CreateConnection() {
    sql::Connection *conn;
    try {
        // 建立连接
        conn = driver->connect(this->url, this->username, this->password);
        if (conn) {
            conn->setSchema(database);
        }
        return conn;
    }
    catch (sql::SQLException &e) {
        ELOG << "create connection error." << e.what();
        return nullptr;
    }
    catch (std::runtime_error &e) {
        ELOG << "[CreateConnection] run time error." << e.what();
        return nullptr;
    }
}

// 从连接池中获得一个连接
sql::Connection *MysqlConnPool::GetConnection() {
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
void MysqlConnPool::ReleaseConnection(sql::Connection *conn) {
    if (conn) {
        pthread_mutex_lock(&lock);
//        std::cout << curSize << " " << minIdleConns << std::endl;
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
MysqlConnPool::~MysqlConnPool() {
    this->DestoryConnPool();
}

// 销毁连接池，需要先销毁连接池的中连接
void MysqlConnPool::DestoryConnPool() {
    list<sql::Connection *>::iterator itCon;
    pthread_mutex_lock(&lock);

    for (itCon = connList.begin(); itCon != connList.end(); ++itCon) {
        // 销毁连接池中的连接
        MysqlConnPool::DestoryConnection(*itCon);
    }
    curSize = 0;
    // 清空连接池中的连接
    connList.clear();

    pthread_mutex_unlock(&lock);
}

// 销毁数据库连接
void MysqlConnPool::DestoryConnection(sql::Connection *conn) {
    if (conn) {
        try {
            conn->close();
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



