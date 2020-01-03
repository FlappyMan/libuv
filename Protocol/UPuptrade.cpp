#include "UPuptrade.h"

void UPUptrade::JsonPack(Json::Value &root)
{
    root["token"] = Json::Value(token());
    root["paypassword"] = Json::Value(paypassword());
    root["marketid"] = Json::Value(marketid());
    root["price"] = Json::Value(price());
    root["num"] = Json::Value(num());
    root["type"] = Json::Value(type());
    if(has_main_coin())
    {
        root["main_coin"] = Json::Value(main_coin());
    }
}

bool UPUptrade::JsonUnpack(Json::Value &root)
{
    set_paypassword(root["paypassword"].asString());
    set_marketid(root["marketid"].asInt64());
    set_price(root["price"].asInt64());
    set_num(root["num"].asInt64());
    set_type(root["type"].asInt());
    set_main_coin(root["main_coin"].asInt());
    return true;
}
