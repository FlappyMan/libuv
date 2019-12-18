

#ifndef _CLIENT_SESSION_HEADER_
#define _CLIENT_SESSION_HEADER_

#include "global.h"
#include "BlockQueue.h"

class ClientSession
{
public:
    ClientSession(uv_tcp_t* tcp);
    ~ClientSession();

    void Init();
    void Destroy();
    bool IsTimeout(time_t tNow);

    int Read(char *pBuffer,int iDataLen);

    void SendPkg(UProtocolBase* pkg);

protected:
    uv_tcp_t * m_tcp;
    UBBuffer m_buffer;

    UBHttpParser m_http;

    time_t m_tLast;
};

#endif
