#ifndef _MATCHDATA_MODEL_HEADER_
#define _MATCHDATA_MODEL_HEADER_

#include "global.h"


class CSellUserModel
{
public:
    CSellUserModel &operator=(const CSellUserModel &obj)
    {
        if (this != &obj)
        {
            this->userid = obj.userid;
            this->num = obj.num;
            this->deal = obj.deal;
            this->xnb = obj.xnb;
            this->xnbd = obj.xnbd;
        }
        return *this;
    }
    CSellUserModel &operator=(UPMatchedData::SellUser& pkg)
    {
        this->userid = pkg.userid();
        this->num = pkg.num();
        this->deal = pkg.deal();
        this->xnb = pkg.xnb();
        this->xnbd = pkg.xnbd();
        return *this;
    }

public:
    string userid;
    string num;
    string deal;
    int xnb;
    int xnbd;
};



class CBuyUserModel
{
public:
    CBuyUserModel &operator=(const CBuyUserModel &obj)
    {
        if (this != &obj)
        {
            this->userid = obj.userid;
            this->num = obj.num;
            this->deal = obj.deal;
            this->cny = obj.cny;
            this->cnyd = obj.cnyd;
        }
        return *this;
    }
    CBuyUserModel &operator=(UPMatchedData::BuyUser& pkg)
    {
        this->userid = pkg.userid();
        this->num = pkg.num();
        this->deal = pkg.deal();
        this->cny = pkg.cny();
        this->cnyd = pkg.cnyd();
        return *this;
    }

public:
    string userid;
    string num;
    string deal;
    int cny;
    int cnyd;
};

class CMatchedDataModel
{
public:
    CMatchedDataModel &operator=(const CMatchedDataModel &obj)
    {
        if (this != &obj)
        {
            this->token = obj.token;
            this->addtime = obj.addtime;
            this->id = obj.id;
            this->price = obj.price;
            this->buyuser = obj.buyuser;
            this->selluser = obj.selluser;
        }
        return *this;
    }
    CMatchedDataModel &operator=(UPMatchedData *pkg)
    {
#warning CMatchedDataModel 记得添加token
        // this->token = dynamic_cast<UPMatchedData *>(pkg)->token();
        this->addtime = dynamic_cast<UPMatchedData *>(pkg)->addtime();
        this->id = dynamic_cast<UPMatchedData *>(pkg)->id();
        this->price = dynamic_cast<UPMatchedData *>(pkg)->price();
        UPMatchedData::BuyUser buy = dynamic_cast<UPMatchedData *>(pkg)->buyuser();
        this->buyuser = buy;
        UPMatchedData::SellUser sell = dynamic_cast<UPMatchedData *>(pkg)->selluser();
        this->selluser = sell;
        return *this;
    }

public:
    string token;
    string addtime;
    int id;
    string price;
    CBuyUserModel buyuser;
    CSellUserModel selluser;
};

#endif
