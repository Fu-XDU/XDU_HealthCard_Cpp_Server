//
// Created by 付铭 on 2022/10/8.
//

#include "mysql.h"
#include "co/defer.h"

MysqlConnPool *mysqlConnPool = nullptr;

int Mysql::StorageThreeCheck(ThreeCheck *threeCheck) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement(
            "INSERT INTO `three_checks`(`openid`, `stu_id`, `passwd`, `location`) VALUES (?, ?, ?, ?)");
    defer(delete pstmt);

    pstmt->setString(1, threeCheck->openid);
    pstmt->setString(2, threeCheck->stuID);
    pstmt->setString(3, threeCheck->passwd);
    pstmt->setString(4, threeCheck->location);
    int updateCount = pstmt->executeUpdate();
    return updateCount;
}

bool Mysql::ThreeCheckRegisteredByOpenid(const std::string &openid) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement("SELECT COUNT(*) FROM `three_checks` WHERE openid = ?");
    defer(delete pstmt);

    pstmt->setString(1, openid);
    sql::ResultSet *res = pstmt->executeQuery();
    res->next();
    int nCount = res->getInt(1);
    return nCount > 0;
}

bool Mysql::ThreeCheckRegisteredByStuid(const std::string &stu_id) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement("SELECT COUNT(*) FROM `three_checks` WHERE stu_id = ?");
    defer(delete pstmt);

    pstmt->setString(1, stu_id);
    sql::ResultSet *res = pstmt->executeQuery();
    res->next();
    int nCount = res->getInt(1);
    return nCount > 0;
}

bool Mysql::ThreeCheckRegistered(const std::string &openid, const std::string &stu_id) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement(
            "SELECT COUNT(*) FROM `three_checks` WHERE openid = ? or stu_id = ?");
    defer(delete pstmt);

    pstmt->setString(1, openid);
    pstmt->setString(2, stu_id);

    sql::ResultSet *res = pstmt->executeQuery();
    res->next();
    int nCount = res->getInt(1);
    return nCount > 0;
}

int Mysql::StorageHealthCard(HealthCard *healthCard) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement(
            "INSERT INTO `health_cards`(`openid`, `stu_id`, `passwd`, `location`) VALUES (?, ?, ?, ?)");
    defer(delete pstmt);

    pstmt->setString(1, healthCard->openid);
    pstmt->setString(2, healthCard->stuID);
    pstmt->setString(3, healthCard->passwd);
    pstmt->setString(4, healthCard->location);
    int updateCount = pstmt->executeUpdate();
    return updateCount;
}

bool Mysql::HealthCardRegisteredByOpenid(const std::string &openid) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement("SELECT COUNT(*) FROM `health_cards` WHERE openid = ?");
    defer(delete pstmt);

    pstmt->setString(1, openid);
    sql::ResultSet *res = pstmt->executeQuery();
    res->next();
    int nCount = res->getInt(1);
    return nCount > 0;
}

bool Mysql::HealthCardRegisteredByStuid(const std::string &stu_id) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement("SELECT COUNT(*) FROM `health_cards` WHERE stu_id = ?");
    defer(delete pstmt);

    pstmt->setString(1, stu_id);
    sql::ResultSet *res = pstmt->executeQuery();
    res->next();
    int nCount = res->getInt(1);
    return nCount > 0;
}

bool Mysql::HealthCardRegistered(const std::string &openid, const std::string &stu_id) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement(
            "SELECT COUNT(*) FROM `health_cards` WHERE openid = ? or stu_id = ?");
    defer(delete pstmt);

    pstmt->setString(1, openid);
    pstmt->setString(2, stu_id);

    sql::ResultSet *res = pstmt->executeQuery();
    res->next();
    int nCount = res->getInt(1);
    return nCount > 0;
}

bool Mysql::DeleteHealthCard(const std::string &openid) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement("DELETE FROM `health_cards` WHERE openid = ?");
    defer(delete pstmt);

    pstmt->setString(1, openid);
    int updateCount = pstmt->executeUpdate();
    return updateCount > 0;
}

bool Mysql::DeleteThreeCheck(const std::string &openid) {
    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement("DELETE FROM `three_checks` WHERE openid = ?");
    defer(delete pstmt);

    pstmt->setString(1, openid);
    int updateCount = pstmt->executeUpdate();
    return updateCount > 0;
}

ThreeCheck Mysql::GetNeededThreeCheckByOpenid(const std::string &openid) {
    bool registered = Mysql::ThreeCheckRegisteredByOpenid(openid);
    ThreeCheck threeCheck = {.id = 0};
    if (!registered) {
        return threeCheck;
    }

    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement(
            "SELECT id,openid,stu_id,location FROM `three_checks` WHERE openid = ?");
    defer(delete pstmt);
    pstmt->setString(1, openid);

    sql::ResultSet *res = pstmt->executeQuery();
    defer(delete res);
    res->afterLast();
    if (res->previous())
        threeCheck = {
                .id = res->getInt("id"),
                .openid = res->getString("openid"),
                .stuID = res->getString("stu_id"),
                .location = res->getString("location"),
        };
    return threeCheck;
}

HealthCard Mysql::GetNeededHealthCardByOpenid(const std::string &openid) {
    bool registered = Mysql::HealthCardRegisteredByOpenid(openid);
    HealthCard healthCard = {.id = 0};
    if (!registered) {
        return healthCard;
    }

    sql::Connection *conn = mysqlConnPool->GetConnection();
    defer(mysqlConnPool->ReleaseConnection(conn));

    sql::PreparedStatement *pstmt = conn->prepareStatement(
            "SELECT id,openid,stu_id,location FROM `health_cards` WHERE openid = ?");
    defer(delete pstmt);
    pstmt->setString(1, openid);

    sql::ResultSet *res = pstmt->executeQuery();
    defer(delete res);
    res->afterLast();
    if (res->previous())
        healthCard = {
                .id = res->getInt("id"),
                .openid = res->getString("openid"),
                .stuID = res->getString("stu_id"),
                .location = res->getString("location"),
        };
    return healthCard;
}