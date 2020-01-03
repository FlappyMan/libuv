#ifndef _LOGIN_DTO_HEADER_
#define _LOGIN_DTO_HEADER_

#include "../global.h"
#include "UPJsonReflex.hpp"


class CLoginDto : public CJsonObjectBase
{
public:
    CLoginDto()
    {
        SetProperty(property(usercount));
        SetProperty(property(password));
    }

public:
    string usercount;
    string password;
};

#endif