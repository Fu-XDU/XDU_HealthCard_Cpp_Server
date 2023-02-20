//
// Created by 付铭 on 2022/10/8.
//

#ifndef XDU_HEALTHCARD_SERVER_MYSQL_H
#define XDU_HEALTHCARD_SERVER_MYSQL_H


#include <mysql/jdbc.h>
#include <iostream>
#include "mysql_conn_pool.h"
#include "../../model/threeCheck.h"
#include "../../model/healthCard.h"

//#define LOG(s) std::cout<<__FILE__<<" : "<<__LINE__<<" "<<__TIMESTAMP__<<" : "<<s<<std::endl;

extern MysqlConnPool *mysqlConnPool;

class Mysql {
public:
    static int StorageThreeCheck(ThreeCheck *threeCheck);

    static bool ThreeCheckRegisteredByOpenid(const std::string &openid);

    static bool ThreeCheckRegisteredByStuid(const std::string &stu_id);

    static bool ThreeCheckRegistered(const std::string &openid, const std::string &stu_id);

    static int StorageHealthCard(HealthCard *healthCard);

    static bool HealthCardRegisteredByOpenid(const std::string &openid);

    static bool HealthCardRegisteredByStuid(const std::string &stu_id);

    static bool HealthCardRegistered(const std::string &openid, const std::string &stu_id);

    static bool DeleteHealthCard(const std::string &openid);

    static bool DeleteThreeCheck(const std::string &openid);

    static ThreeCheck GetNeededThreeCheckByOpenid(const std::string &openid);

    static HealthCard GetNeededHealthCardByOpenid(const std::string &openid);
};

#endif //XDU_HEALTHCARD_SERVER_MYSQL_H
