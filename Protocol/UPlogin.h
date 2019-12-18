#ifndef _UPLOGIN_H_
#define _UPLOGIN_H_

#include "UBaseLib.h"
#include "proto/ukex.login.pb.h"
#include "UProtocolBase.h"

class UPLogin : public UProtocolBase, public ukex::login
{
public:
	UPLogin(){};
	virtual ~UPLogin(){};

	void JsonPack(Json::Value &root){};
    bool JsonUnpack(Json::Value &root){return true;};
};

#endif
