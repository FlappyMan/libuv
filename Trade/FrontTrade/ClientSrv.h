
#ifndef _CLIENT_SRV_HEADER_
#define _CLIENT_SRV_HEADER_

#include "ClientSession.h"
#include "BackTradeSrv.h"

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
    map<uv_tcp_t*,ClientSession*> m_mSession;
    
    //queue<UProtocolBase*> m_qRequest;
    BlockQueue<UProtocolBase*> m_qRequest;
    // uv_mutex_t m_lock;
    BackTradeSrv m_btSrv;
};


#endif
