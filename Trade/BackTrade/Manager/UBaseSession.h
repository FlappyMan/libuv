#ifndef _BASE_SESSION_HEADER_
#define _BASE_SESSION_HEADER_
#include "../global.h"
class CBaseRequest;

class CBaseSession
{
public:
    CBaseSession();
    ~CBaseSession();
public:
    string PraseOperation();
    virtual int OnRecv(uv_tcp_t *client,char *pBuffer, int iDataLen);
    bool isRecvFinish(){return m_bRecvFinish;}
    bool isMoveToUC(){return m_bMoveToUC;}
    bool setMoveToUC(bool b = true){m_bMoveToUC = b;}
    UBBuffer* getRecvBuff(){return &m_buffer;}
    uv_tcp_t * getClientFd(){return m_client;}
private:
    UBBuffer m_buffer;
    uint32_t m_uiValueLen;
    uint16_t m_usType;
    uv_tcp_t *m_client;
    bool m_bMoveToUC;
    bool m_bRecvFinish;
};

#endif
