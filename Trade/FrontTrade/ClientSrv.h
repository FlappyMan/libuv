
#ifndef _CLIENT_SRV_HEADER_
#define _CLIENT_SRV_HEADER_

#include "ClientSession.h"

class ClientSrv
{
    public:
        ClientSrv();
        ~ClientSrv();

        void NewConnection(uv_tcp_t* tcp);
        int Read(uv_tcp_t *tcp,char *pBuffer,int iDataLen); 
        void PushResponse(BlockQueue<UProtocolBase*> &res);
        void GetRequest(BlockQueue<UProtocolBase*> &req);
        void OnTimer(time_t tNow);
    public:
        void _DispatchPkg(UProtocolBase* pkg);

    public:
        map<uv_tcp_t*,ClientSession*> m_mSession;
        map<string,uv_tcp_t*> m_mClientID;
        BlockQueue<UProtocolBase*> m_qRequest;
        BlockQueue<UProtocolBase*> m_qResponse;
};


#endif
