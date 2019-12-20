

#ifndef _CLIENT_SESSION_HEADER_
#define _CLIENT_SESSION_HEADER_

#include "global.h"
#include "BlockQueue.h"
#include "ThreadBackTrade.h"

class ClientSession
{
public:
    ClientSession(uv_tcp_t* tcp);
    ~ClientSession();

    void Init();
    void Destroy();
    bool IsTimeout(time_t tNow);

    int Read(uv_tcp_t* client, char *pBuffer,int iDataLen);

    void SendPkg(uv_tcp_t* client, UProtocolBase* pkg);

public:
    uv_tcp_t * m_tcp;
    UBBuffer m_buffer;
    BlockQueue<UProtocolBase*> m_qRequest;
    UBHttpParser m_http;
    map<string, map<uv_tcp_t*,UProtocolBase*>> m_tokenPackage;

    time_t m_tLast;
};

#endif
