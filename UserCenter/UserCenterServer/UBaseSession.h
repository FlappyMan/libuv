#ifndef _BASE_SESSION_HEADER_
#define _BASE_SESSION_HEADER_
#include "global.h"
class CBaseSession
{
public:
    CBaseSession();
    ~CBaseSession();
public:
    virtual int OnRecv(uv_tcp_t *client,char *pBuffer, int iDataLen);

private:
    UBBuffer m_buffer;
    uint16_t m_uiType;
    uint32_t m_uiValueLen;
};

#endif
