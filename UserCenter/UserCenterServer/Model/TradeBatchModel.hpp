#ifndef _TRADEBATCH_MODEL_HEADER_
#define _TRADEBATCH_MODEL_HEADER_

#include "../global.h"

class CTradeInfoModel
{
public:
    CTradeInfoModel &operator=(const CTradeInfoModel &obj)
    {
        if (this != &obj)
        {
            this->marketid = obj.marketid;
            this->price = obj.price;
            this->num = obj.num;
            this->type = obj.type;
        }

        return *this;
    }
    CTradeInfoModel &operator=(UPUptradebatch::Trades& pkg)
    {
        this->price = pkg.price();
        this->marketid = pkg.marketid();
        this->num = pkg.num();
        this->type = pkg.type();
        return *this;
    }

public:
    int marketid;
    int price;
    int num;
    int type;
};

class CTradeBatchModel
{
public:
    CTradeBatchModel &operator=(const CTradeBatchModel &obj)
    {
        if (this != &obj)
        {
            this->token = obj.token;
            this->paypassword = obj.paypassword;
            this->trades = obj.trades;
        }

        return *this;
    }
    CTradeBatchModel &operator=(UPUptradebatch *pkg)
    {
#warning CTradeBatchModel 记得添加token
        // this->token = dynamic_cast<UPUptradebatch *>(pkg)->token();
        this->paypassword = dynamic_cast<UPUptradebatch *>(pkg)->paypassword();
        int iSize = dynamic_cast<UPUptradebatch *>(pkg)->trades_size();
        for (int iLoop = 0; iLoop < iSize; iLoop++)
        {
            CTradeInfoModel model;
            UPUptradebatch::Trades trade = dynamic_cast<UPUptradebatch *>(pkg)->trades(iLoop);
            model = trade;
            this->trades.push_back(model);
        }
        return *this;
    }

public:
    string token;
    string paypassword;
    list<CTradeInfoModel> trades;
};

#endif
