#include "UPAuth.h"

bool UPAuth::JsonParser(string& sub, Json::Value &root)
{
    sub = root["auth"].asString();
    return true;
}