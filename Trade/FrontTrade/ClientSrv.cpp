
#include "ClientSrv.h"
#include "ThreadClient.h"

ClientSrv::ClientSrv()
{
    // uv_mutex_init(&m_lock);
}

ClientSrv::~ClientSrv()
{

}

void ClientSrv::NewConnection(uv_tcp_t* tcp)
{
    ClientSession *p=new ClientSession(tcp);
    p->Init();
    m_mSession.insert(pair<uv_tcp_t*,ClientSession*>(tcp,p));
}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int ClientSrv::Read(uv_tcp_t* tcp,char *pBuffer,int iDataLen)
{
    map<uv_tcp_t*,ClientSession*>::iterator it=m_mSession.find(tcp);
    if(it==m_mSession.end())return false;

    return it->second->Read(tcp, pBuffer, iDataLen,m_qRequest,m_mClientID);
}

void ClientSrv::PushResponse(BlockQueue<UProtocolBase*> &res)
{
    while (res.size()>0)
    {
        m_qResponse.put(res.get());
    }
}

void ClientSrv::GetRequest(BlockQueue<UProtocolBase*> &req)
{
    while (req.size()>0)
    {
        req.put(m_qRequest.get());
    }
}

void ClientSrv::OnTimer(time_t tNow)
{
    map<uv_tcp_t*,ClientSession*>::iterator it;
    for(it=m_mSession.begin();it!=m_mSession.end();it++)
    {
        if (it->second->IsTimeout(tNow))
        {
            it->second->Destroy();
            delete it->second;
            m_mSession.erase(it);
            continue;
        }
    }  
    while(m_qResponse.size()>0)
    {
        _DispatchPkg(m_qResponse.get());
    }   
}

void ClientSrv::_DispatchPkg(UProtocolBase* pkg)
{
    UPResponse *res = (UPResponse *)pkg;
    map<string,uv_tcp_t*>::iterator it = m_mClientID.begin();
    for (; it!=m_mClientID.end(); it++)
    {
        if (strcasecmp(it->first.c_str(),res->token().c_str()) == 0)
        {
            Client_Write((uv_stream_t*)it->second,res,200);
        }     
    }
    
}

