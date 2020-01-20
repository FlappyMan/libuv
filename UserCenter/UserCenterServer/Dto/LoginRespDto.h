#ifndef _LOGINRESP_DTO_HEADER_
#define _LOGINRESP_DTO_HEADER_

#include "../global.h"
#include "UPJsonReflex.hpp"

class CLoginRespDto : public CJsonObjectBase
{
public:
    CLoginRespDto()
    {
        SetProperty(property(token));
        SetProperty(property(status));
        SetProperty(property(deadLine));
    }
    CJsonObjectBase * requestOperation(){};
public:
    string token;
    string status;
    string deadLine;
};

#endif