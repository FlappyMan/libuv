#ifndef _LOGIN_DTO_HEADER_
#define _LOGIN_DTO_HEADER_

#include "global.h"
#include "CJsonObjectBase.hpp"


class CLoginDto : public CJsonObjectBase
{
public:
    CLoginDto(){SetPropertys();}
protected:
    //子类需要实现此函数，并且将相应的映射关系进行设置
    virtual void SetPropertys()
    {
        SetProperty(property(usercount));
        SetProperty(property(password));
    }

public:
    string usercount;
    string password;
    int test;
};

#endif