

#ifndef _BACKTRADE_SESSION_HEADER_
#define _BACKTRADE_SESSION_HEADER_

#include "global.h"
#include "BlockQueue.h"
class BackTradeSrv;
class BackTradeSyncFile
{
    public:
        string m_sRelativePath;
        string m_sFileName;
};

class BackTradeSession
{
    public:
        BackTradeSession(uv_tcp_t *tcp,BlockQueue<UProtocolBase*> &qRes);
        ~BackTradeSession();

        void Init();

        int Read(char *pBuffer,int iDataLen, BlockQueue<UProtocolBase*> &m_qResponse);
        bool IsTimeout(time_t tNow);
    protected:
        bool LoginCheck(UPLogin *pLogin);

    protected:
        const uv_tcp_t* m_tcp;
        UBBuffer m_buffer;
	    BackTradeSrv *m_pSrv;   
    public:
        bool m_bLogined;
        string m_sMarkID;
        time_t m_tLast;
};

#endif
