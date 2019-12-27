
#include "ClientSrv.h"

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

    return it->second->Read(tcp, pBuffer, iDataLen,this->m_qRequest);
}


void ClientSrv::PushRequest(BlockQueue<UProtocolBase*> &q)
{
    // uv_mutex_lock(&m_lock);
    // while(q.size()>0)
    // {
    //     m_qRequest.push(q.front());
    //     q.pop();
    // }
    // uv_mutex_unlock(&m_lock);
    // Client json->pb request
    m_qRequest.put(q.get());//BackTrade pb response
}


void ClientSrv::OnTimer(time_t tNow)
{
    // queue<UProtocolBase*> qReq;
    // uv_mutex_lock(&m_lock);
    // qReq.swap(m_qReqest);
    // uv_mutex_unlock(&m_lock);

    // while(qReq.size()>0)
    // {
    //     delete qReq.front();
    //     qReq.pop();
    // }
    BlockQueue<UProtocolBase* > qReq;
    qReq = m_qRequest;
    map<uv_tcp_t*,ClientSession*>::iterator it;
    UProtocolBase* pkg = NULL;  
    while(qReq.size()>0)
    {
        pkg = qReq.get();
        for(it=m_mSession.begin();it!=m_mSession.end();it++)
        {
            if (it->second->IsTimeout(tNow))
            {
                it->second->Destroy();
                delete it->second;
                it = m_mSession.erase(it);
                continue;
            }
            for (map<uv_tcp_t*,BackTradeSession*>::iterator iter = m_btSrv.m_mSession.begin();iter!=m_btSrv.m_mSession.end();iter++)
            {
                it->second->SendPkg(iter->first, pkg);//客户端的Request发送给Server
            }
        }
        
    }
}

