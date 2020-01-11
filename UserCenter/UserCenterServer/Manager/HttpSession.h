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
    
public:
    CJsonObjectBase *m_pObject;
    
private:
    bool m_bRecvFinish;
};

#endif
