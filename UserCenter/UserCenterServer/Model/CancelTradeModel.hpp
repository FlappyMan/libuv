#ifndef _CANCELTRADE_MODEL_HEADER_
#define _CANCELTRADE_MODEL_HEADER_

#include "../global.h"
class CCancelTradeModel
{
public:
    CCancelTradeModel &operator=(const CCancelTradeModel &obj)
    {
        if (this != &obj)
        {
            this->id = obj.id;
        }
        return *this;
    }
    CCancelTradeModel &operator=(UPCanceltrade *pkg)
    {
#warning CCancelTradeModel 记得添加token
        // this->token = dynamic_cast<UPCanceltrade *>(pkg)->token();
        this->id = dynamic_cast<UPCanceltrade *>(pkg)->id();
        return *this;
    }

public:
    string token;
    int id;
};

#endif
