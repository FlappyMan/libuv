#include "UPresponse.h"

void UPResponse::JsonPack(Json::Value &root)
{
    root["status"] = status();
    root["data"] = data();
}

bool UPResponse::JsonUnpack(Json::Value &root)
{
    set_status(root["status"].asUInt());
    set_data(root["data"].asString());
    return true;
}
