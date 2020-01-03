
#ifndef _BACKTRADE_SRV_HEADER_
#define _BACKTRADE_SRV_HEADER_

#include "BackTradeSession.h"

class BackTradeSrv
{
    public:
        BackTradeSrv();
        ~BackTradeSrv();

        void NewConnection(uv_tcp_t *tcp);
        int Read(uv_tcp_t *tcp,char *pBuffer,int iDataLen);
        void OnTimer(time_t tNow);
        void GetResponse(BlockQueue<UProtocolBase*> &res);
        void PushRequest(BlockQueue<UProtocolBase*> &req);
        void _DispatchReq(UProtocolBase* req);
    public:
        map<uv_tcp_t*,BackTradeSession*> m_mSession;
        map<int64_t,BackTradeSession*> m_mMarket;
        BlockQueue<UProtocolBase*> m_qResponse;
        BlockQueue<UProtocolBase*> m_qRequest;

    public:
        string m_sPublicKey;  
};

#endif
