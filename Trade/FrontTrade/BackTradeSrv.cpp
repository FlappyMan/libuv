
#include "BackTradeSrv.h"
#include "ThreadClient.h"

BackTradeSrv::BackTradeSrv()
{

}

BackTradeSrv::~BackTradeSrv()
{

}

void BackTradeSrv::NewConnection(uv_tcp_t *tcp)
{
    BackTradeSession *p=new BackTradeSession(tcp,m_qResponse);
    p->Init();
    m_mSession.insert(pair<uv_tcp_t*,BackTradeSession*>(tcp,p));
}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int BackTradeSrv::Read(uv_tcp_t* tcp,char *pBuffer,int iDataLen)
{
    map<uv_tcp_t*,BackTradeSession*>::iterator it=m_mSession.find(tcp);
    if(it==m_mSession.end())return false;

    return it->second->Read(pBuffer,iDataLen,m_qResponse);
}

void BackTradeSrv::OnTimer(time_t tNow)
{
    map<uv_tcp_t*,BackTradeSession*>::iterator it;
    UProtocolBase* pkg = NULL; 
    for(it=m_mSession.begin();it!=m_mSession.end();it++)
    {
        if (it->second->IsTimeout(tNow))
        {
            delete it->second;
            m_mSession.erase(it);
            continue;
        }
    }
    while (m_qRequest.size()>0)
    {
        _DispatchReq(m_qRequest.get());//Client Request
    }   
}

void BackTradeSrv::_DispatchReq(UProtocolBase* pkg)
{ 
    if (!pkg)return;
    switch(pkg->m_uiType)
    {
        case UPUptrade::CMD :
            //BackTrade_Write((uv_stream_t *)server, dynamic_cast<UPUptrade *>(pkg), SIZE_BUFFER_2k);
            break;
        case UPUptradebatch::CMD :
            /*code*/
            break;
        case UPCanceltrade::CMD :
            //BackTrade_Write((uv_stream_t *)server, dynamic_cast<UPUptrade *>(pkg), SIZE_BUFFER_2k);
            break;
        case UPCanceltradebatch::CMD :
            /*code*/
            break;
        default:
            break;
    }
}

void BackTradeSrv::GetResponse(BlockQueue<UProtocolBase*> &res)
{
    while (m_qResponse.size() > 0)
    {
        res.put(m_qResponse.get());
    }
    
}

void BackTradeSrv::PushRequest(BlockQueue<UProtocolBase*> &req)
{
    while (req.size()>0)
    {
        m_qRequest.put(req.get());
    }
    
}