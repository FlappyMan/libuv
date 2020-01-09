#ifndef _LOGIN_DTO_HEADER_
#define _LOGIN_DTO_HEADER_

#include "../global.h"
#include "UPJsonReflex.hpp"


class CLoginDto : public CJsonObjectBase
{
public:
    CLoginDto();
    CJsonObjectBase * requestOperation();
    void respDtoSerialize(){};
public:
    string usercount;
    string password;
};

#endif