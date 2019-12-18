
#include "BackTradeSrv.h"

BackTradeSrv::BackTradeSrv()
{
    // uv_mutex_init(&m_lock);
}

BackTradeSrv::~BackTradeSrv()
{

}


void BackTradeSrv::NewConnection(uv_tcp_t *tcp)
{
    BackTradeSession *p=new BackTradeSession(tcp,m_qReqest);
    p->Init();
}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int BackTradeSrv::Read(uv_tcp_t* tcp,char *pBuffer,int iDataLen)
{
    map<uv_tcp_t*,BackTradeSession*>::iterator it=m_mSession.find(tcp);
    if(it==m_mSession.end())return false;

    return it->second->Read(pBuffer,iDataLen);
}


void BackTradeSrv::GetRequest(BlockQueue<UProtocolBase*> &q)
{
    // uv_mutex_lock(&m_lock);
    // q.swap(m_qReqest);
    // uv_mutex_unlock(&m_lock);
    q = m_qReqest;
}
