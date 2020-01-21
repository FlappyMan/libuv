#include "UPcanceltradebatch.h"

void UPCanceltradebatch::JsonPack(Json::Value &root)
{
    Json::Value& array = root["ids"];
    Json::Value data;
    for(int i = 0; i < ids_size(); ++i)
    {
        data = ids(i);
        array.append(data);
    }
    root["marketid"] = marketid();
}

bool UPCanceltradebatch::JsonUnpack(Json::Value &root)
{
    if(root["ids"].isArray() == false)
        return false;
    for(uint32_t i = 0; i < root["ids"].size(); ++i)
    {
        add_ids(root["ids"][i].asUInt64());
    }
    set_marketid(root["marketid"].asUInt64());
    return true;
}
