﻿#pragma once
#include <string>
class CmdResalt
{
public:
    CmdResalt(bool success, const std::string &msg = "");
    operator bool() const;
    operator const std::string &() const;

private:
    bool        success;
    std::string msg;
};

#define RunTimeAssert(condition, msg) \
    if(!(condition))                  \
    {                                 \
        throw CmdResalt(false, msg);  \
    }