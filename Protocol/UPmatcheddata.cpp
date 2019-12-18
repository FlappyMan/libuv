#include "UPmatcheddata.h"

void UPMatchedData::JsonPack(Json::Value &root)
{
    root["addtime"] = addtime();
    root["id"] = id();
    root["price"] = price();
    BuyUser buyUser = buyuser();
    Json::Value& bitem = root["buyuser"];
    bitem["userid"] = buyUser.userid();
    bitem["num"] = buyUser.num();
    bitem["deal"] = buyUser.deal();
    bitem["cny"] = buyUser.cny();
    bitem["cnyd"] = buyUser.cnyd();

    SellUser sellUser = selluser();
    Json::Value& sitem = root["SellUser"];
    sitem["userid"] = sellUser.userid();
    sitem["num"] = sellUser.num();
    sitem["deal"] = sellUser.deal();
    sitem["xnb"] = sellUser.xnb();
    sitem["xnbd"] = sellUser.xnbd();
}

bool UPMatchedData::JsonUnpack(Json::Value &root)
{
    set_addtime(root["addtime"].asString());
    set_id(root["id"].asUInt());
    set_price(root["price"].asString());
    BuyUser* bUser = mutable_buyuser();
    Json::Value& bitem = root["buyuser"];
    bUser->set_userid(bitem["userid"].asString());
    bUser->set_num(bitem["num"].asString());
    bUser->set_deal(bitem["deal"].asString());
    bUser->set_cny(bitem["cny"].asUInt64());
    bUser->set_cnyd(bitem["cnyd"].asUInt64());

    SellUser* sUser = mutable_selluser();
    Json::Value& sitem = root["SellUser"];
    sUser->set_userid(sitem["userid"].asString());
    sUser->set_num(sitem["num"].asString());
    sUser->set_deal(sitem["deal"].asString());
    sUser->set_xnb(sitem["xnb"].asUInt64());
    sUser->set_xnbd(sitem["xnbd"].asUInt64());
    return true;
}
