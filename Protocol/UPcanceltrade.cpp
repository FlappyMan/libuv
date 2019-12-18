#include "UPcanceltrade.h"

void UPCanceltrade::JsonPack(Json::Value &root)
{
    root["id"] = id();
}

bool UPCanceltrade::JsonUnpack(Json::Value &root)
{
    set_id(root["id"].asUInt64());
    return true;
}
