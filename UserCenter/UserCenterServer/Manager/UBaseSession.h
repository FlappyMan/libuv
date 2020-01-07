#ifndef _BASE_SESSION_HEADER_
#define _BASE_SESSION_HEADER_
#include "../global.h"
// #include "BaseRequestOper.h"
class CBaseRequestOper;

class CBaseSession
{
public:
    CBaseSession();
    ~CBaseSession();
public:
    virtual int OnRecv(uv_tcp_t *client,char *pBuffer, int iDataLen);
    CBaseRequestOper* PraseOperation();
    bool isRecvFinish(){return m_bRecvFinish;}
private:
    UBBuffer m_buffer;
    uint16_t m_uiType;
    uint32_t m_uiValueLen;
    uv_tcp_t *m_client;
    bool m_bRecvFinish;
};

#endif
