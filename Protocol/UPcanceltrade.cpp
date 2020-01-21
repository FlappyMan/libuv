#include "UPcanceltrade.h"

void UPCanceltrade::JsonPack(Json::Value &root)
{
    root["id"] = id();
    root["marketid"] = marketid();
}

bool UPCanceltrade::JsonUnpack(Json::Value &root)
{
    set_id(root["id"].asUInt64());
    set_marketid(root["marketid"].asUInt64());
    return true;
}
