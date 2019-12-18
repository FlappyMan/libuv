#include "UPSubscribe.h"

bool UPSubscribe::JsonParser(Json::Value &root,string& sub)
{
    sub = root["sub"].asString();
    return true;
}