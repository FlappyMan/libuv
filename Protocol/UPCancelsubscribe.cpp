#include "UPCancelsubscribe.h"

bool UPCancelSubscribe::JsonParser(string& sub, Json::Value &root)
{
    sub = root["cancelsub"].asString();
    return true;
}