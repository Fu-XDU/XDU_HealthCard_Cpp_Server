//
// Created by 付铭 on 2022/10/8.
//

#ifndef XDU_HEALTHCARD_SERVER_MYSQL_H
#define XDU_HEALTHCARD_SERVER_MYSQL_H


#include <mysql/jdbc.h>
#include <iostream>
#include "connection_pool.h"
#include "../model/threeCheck.h"

//#define LOG(s) std::cout<<__FILE__<<" : "<<__LINE__<<" "<<__TIMESTAMP__<<" : "<<s<<std::endl;

extern ConnPool *connPool;

class Mysql {
public:
    static int StorageThreeCheck(ThreeCheck *threeCheck);
};

#endif //XDU_HEALTHCARD_SERVER_MYSQL_H
