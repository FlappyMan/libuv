#ifndef _UPSUBSCRIBE_H_
#define _UPSUBSCRIBE_H_
#include "UBaseLib.h"
#include "UProtocolBase.h"

class UPSubscribe : public UProtocolBase
{
    public:
        UPSubscribe(){};
        virtual ~UPSubscribe(){};

        void JsonPack(Json::Value &root){};
        bool JsonUnpack(Json::Value &root){return true;};

        bool JsonParser(string& sub, Json::Value &root);
    public:
        static constexpr const char* CMD_WSAPI = "sub";//WS
        //static constexpr const char* CMD_WEBAPI = "/api/private/subscribe";//HTTP
        //static constexpr const char* CMD_ROBOTAPI = "/api/private/subscribe";//robot http    
};


#endif
