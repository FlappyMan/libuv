
#ifndef _CLIENT_SRV_HEADER_
#define _CLIENT_SRV_HEADER_

#include "ClientSession.h"
#include "UProtocol.h"

extern UBHttpParser hp;

class ClientSrv
{
public:
    ClientSrv();
    ~ClientSrv();

    void NewConnection(uv_tcp_t* tcp);
    int Read(uv_tcp_t *tcp,char *pBuffer,int iDataLen);

    void PushRequest(BlockQueue<UProtocolBase*> &q);
    void OnTimer(time_t tNow);
public:


protected:
    map<uv_tcp_t*,ClientSession*> m_mSession;
    
    //queue<UProtocolBase*> m_qReqest;
    BlockQueue<UProtocolBase*> m_qReqest;
    // uv_mutex_t m_lock;
};


#endif
