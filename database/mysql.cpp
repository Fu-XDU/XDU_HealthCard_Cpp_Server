//
// Created by 付铭 on 2022/10/8.
//

#include "mysql.h"

ConnPool *connPool = nullptr;

int Mysql::StorageThreeCheck(ThreeCheck *threeCheck) {
    sql::Connection *conn = connPool->GetConnection();
    conn->setSchema("test");
    sql::PreparedStatement *pstmt = conn->prepareStatement(
            "INSERT INTO `test`.`three_checks`(`openid`, `stu_id`, `passwd`, `location`) VALUES (?, ?, ?, ?)");
    pstmt->setString(1, threeCheck->openid);
    pstmt->setString(2, threeCheck->stuID);
    pstmt->setString(3, threeCheck->passwd);
    pstmt->setString(4, threeCheck->location);
    int updateCount = pstmt->executeUpdate();

    delete pstmt;
    connPool->ReleaseConnection(conn);
    return updateCount;
}


//    sql::ResultSet *res = pstmt->executeQuery();
//    res->afterLast();
//    while (res->previous())
//        std::cout << "\t... MySQL counts: " << res->getInt("id") << endl;
//    delete res;