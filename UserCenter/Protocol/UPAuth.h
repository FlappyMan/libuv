#ifndef _UPAUTH_H_
#define _UPAUTH_H_
#include "UBaseLib.h"
#include "UProtocolBase.h"

class UPAuth : public UProtocolBase
{
    public:
        UPAuth(){};
        virtual ~UPAuth(){};

        void JsonPack(Json::Value &root){};
        bool JsonUnpack(Json::Value &root){return true;};

        bool JsonParser(string& sub, Json::Value &root);
    public:
        static constexpr const char* CMD_WSAPI = "auth";//WS
        //static constexpr const char* CMD_WEBAPI = "/api/private/subscribe";//HTTP
        //static constexpr const char* CMD_ROBOTAPI = "/api/private/subscribe";//robot http    
};


#endif
