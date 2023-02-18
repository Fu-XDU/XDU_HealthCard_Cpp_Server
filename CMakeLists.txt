cmake_minimum_required(VERSION 3.23)
project(XDU_HealthCard_Server)

set(CMAKE_CXX_STANDARD 23)

include_directories(/usr/local/include/hv /usr/local/mysql-connector-c++/include /usr/local/include/hiredis)
link_directories(/usr/local/lib /usr/local/mysql-connector-c++/lib64)

find_package(coost REQUIRED CONFIG)


add_executable(XDU_HealthCard_Server main.cpp routes/router.cpp
        routes/router.h controller/serveController.cpp controller/serveController.h
        controller/authController.cpp controller/authController.h
        model/base/baseResponse.h utils/utils.cpp utils/utils.h
        model/threeCheck.h model/base/retCodeDef.h service/serveService.cpp
        service/serveService.h database/mysql/mysql.cpp database/mysql/mysql.h
        database/mysql/mysql_conn_pool.cpp database/mysql/mysql_conn_pool.h utils/flag.h utils/flag.cpp database/redis/redis_conn_pool.cpp database/redis/redis_conn_pool.h database/redis/redis.cpp database/redis/redis.h)

target_link_libraries(XDU_HealthCard_Server -lhv -lhiredis -lmysqlcppconn coost::co)