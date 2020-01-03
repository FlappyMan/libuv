#ifndef _TRADE_MODEL_HEADER_
#define _TRADE_MODEL_HEADER_

#include "../global.h"
class CTradeModel
{
public:
    CTradeModel &operator=(const CTradeModel &obj)
    {
        if (this != &obj)
        {
            this->token = obj.token;
            this->paypassword = obj.paypassword;
            this->marketid = obj.marketid;
            this->price = obj.price;
            this->num = obj.num;
            this->type = obj.type;
            this->main_coin = obj.main_coin;
        }
        return *this;
    }
    CTradeModel &operator=(UPUptrade *pkg)
    {
        this->token = dynamic_cast<UPUptrade *>(pkg)->token();
        this->paypassword = dynamic_cast<UPUptrade *>(pkg)->paypassword();
        this->marketid = dynamic_cast<UPUptrade *>(pkg)->marketid();
        this->price = dynamic_cast<UPUptrade *>(pkg)->price();
        this->num = dynamic_cast<UPUptrade *>(pkg)->num();
        this->type = dynamic_cast<UPUptrade *>(pkg)->type();
        this->main_coin = dynamic_cast<UPUptrade *>(pkg)->main_coin();
        return *this;
    }

public:
    string token;
    string paypassword;
    int marketid;
    int price;
    int num;
    int type;
    int main_coin;
};

#endif
