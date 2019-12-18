#include "UPuptradebatch.h"

void UPUptradebatch::JsonPack(Json::Value &root)
{
    root["paypassword"] = paypassword();
    Json::Value& array=root["trades"];  
    Json::Value trade;
    for(int i = 0; i < trades_size(); ++i)
    {
        const Trades& tmpTrade = trades(i);       
        trade["marketid"] = tmpTrade.marketid();
        trade["price"] = tmpTrade.price();
        trade["num"] = tmpTrade.num();
        trade["type"] = tmpTrade.type();
        array.append(trade);  
        trade.clear();
    }
}

bool UPUptradebatch::JsonUnpack(Json::Value &root)
{
    if(root["trades"].isArray() == false)return false;
    set_paypassword(root["paypassword"].asString());
    Trades* pTrades = NULL;
    for(uint32_t i=0; i < root["trades"].size(); ++i)
    {
        Json::Value& item = root["trades"][i];      
        pTrades = add_trades();
        pTrades->set_marketid(item["marketid"].asUInt64());
        pTrades->set_price(item["price"].asUInt64());
        pTrades->set_num(item["num"].asUInt64());
        pTrades->set_type(item["type"].asUInt());
    }
    return true;
}