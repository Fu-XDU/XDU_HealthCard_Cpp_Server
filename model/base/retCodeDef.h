//
// Created by 付铭 on 2022/10/6.
//

#ifndef XDU_HEALTHCARD_SERVER_RETCODEDEF_H
#define XDU_HEALTHCARD_SERVER_RETCODEDEF_H


struct RET_CODE {
    int code;
    std::string message;
};

static RET_CODE SUCCESS{0, "Success"};
static RET_CODE BindDataFailed{10001, "Bind data failed"};
static RET_CODE ConnectMysqlFailed{20001, "Connect mysql failed"};


static RET_CODE CannotSubmitAgain{30011, "Cannot submit again"};
static RET_CODE RedisCurdFailed{30012, "Redis curd failed"};
static RET_CODE MysqlCurdFailed{30013, "Mysql curd failed"};
static RET_CODE NotRegistered{30014, "Not registered yet"};



//NewJwtFailed       = NewRetCode(30001, "New jwt failed")
//Unauthorized       = NewRetCode(30002, "Unauthorized")
//LoginXidianFailed  = NewRetCode(30003, "Login xidian failed")
//ConnectWxFailed    = NewRetCode(30004, "Connect wx server failed")
//SetRedisLockFailed = NewRetCode(30005, "Set redis lock failed")
//WxServerBusy       = NewRetCode(30006, "System is busy, please try again later")
//CodeInvalid        = NewRetCode(30007, "Code invalid")
//FrequencyLimit     = NewRetCode(30008, "Frequency limit, 100 times per minute per user")
//HighRiskUser       = NewRetCode(30009, "High-risk user, login interception")
//LockExist          = NewRetCode(30010, "Redis lock has existed")
//CannotSubmitAgain  = NewRetCode(30011, "Cannot submit again")
//RedisCurdFailed    = NewRetCode(30012, "Redis curd failed")

#endif //XDU_HEALTHCARD_SERVER_RETCODEDEF_H
