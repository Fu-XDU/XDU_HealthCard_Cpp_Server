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
static RET_CODE InsertDataFailed{20002, "Insert data failed"};

#endif //XDU_HEALTHCARD_SERVER_RETCODEDEF_H
