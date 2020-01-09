#ifndef _HTTP_SESSION_HEADER_
#define _HTTP_SESSION_HEADER_
#include "../global.h"
#include "../Protocol/UPJsonReflex.hpp"
class CHttpSession
{
public:
    CHttpSession();
    ~CHttpSession();
public:
    virtual int OnRecv(uv_tcp_t *client,char *pBuffer, int iDataLen);
    bool isRecvFinish(){return m_bRecvFinish;}
    CJsonObjectBase * getObject(){return m_pObject;}
private:
    UBBuffer m_buffer;
    uint16_t m_uiType;
    uint32_t m_uiValueLen;
    UBHttpParser m_http;
    bool m_bRecvFinish;
    CJsonObjectBase *m_pObject;
};

#endif
