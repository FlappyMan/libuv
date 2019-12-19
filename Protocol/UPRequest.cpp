#include "UPRequest.h"

bool UPRequest::JsonParser(string& sub, Json::Value &root)
{
    sub = root["req"].asString();
    return true;
}