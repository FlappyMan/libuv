#ifndef _HTTP_SESSION_HEADER_
#define _HTTP_SESSION_HEADER_
#include "global.h"
class CHttpSession
{
public:
    CHttpSession();
    ~CHttpSession();
public:
    virtual int OnRecv(uv_tcp_t *client,char *pBuffer, int iDataLen);

private:
    UBBuffer m_buffer;
    uint16_t m_uiType;
    uint32_t m_uiValueLen;
    UBHttpParser m_http;
};

#endif
