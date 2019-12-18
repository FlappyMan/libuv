
#ifndef _UPROTOCOL_BASE_HEADER_
#define _UPROTOCOL_BASE_HEADER_

#include "UBaseLib.h"

class UProtocolBase
{
public:
    UProtocolBase():m_uiType(0),m_uiPkgLength(0){};
    virtual ~UProtocolBase(){};

    virtual void JsonPack(Json::Value &root)=0;
    virtual bool JsonUnpack(Json::Value &root)=0;
public:
    uint16_t m_uiType;      // 包类型
    uint32_t m_uiPkgLength; // 打包后长度，使用时注意场景
};

class UVWriteReq
{
public:
    UVWriteReq():len(0),pkg(NULL){};
    UVWriteReq(UProtocolBase *p):len(0),pkg(p){};
    virtual ~UVWriteReq()
    {
        if(pkg!=NULL)delete pkg;
    };

    void Reset(){len=0;if(pkg){delete pkg;pkg=NULL;};};
public:
    uv_write_t req;
    uv_buf_t buf;
    uint32_t len;           // buf 中实际数据长度
    UProtocolBase *pkg;
};

#endif
