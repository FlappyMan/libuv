#include "ClientSession.h"

ClientSession::ClientSession(uv_tcp_t* tcp):m_tcp(tcp)
{

}

ClientSession::~ClientSession()
{

}

void ClientSession::Init()
{
    m_tLast = time(NULL);
    m_http.Init(HTTP_REQUEST);
}

void ClientSession::Destroy()
{
    m_http.Destroy();
}

bool ClientSession::IsTimeout(time_t tNow)
{
    return tNow > m_tLast+30;
}

void ClientSession::SendPkg(UProtocolBase* pkg)
{
    m_tLast = time(NULL);
    switch (pkg->m_uiType)
    {
    case UPUptrade::CMD :
        /* code */
        break;
    
    default:
        break;
    }
}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int ClientSession::Read(char *pBuffer,int iDataLen)
{
    int iTotalDataLen=m_buffer.AppendData(pBuffer,iDataLen);
    int ret = m_http.Readed(pBuffer,iDataLen);
    if(ret<0)return -1;
    if(ret>0)return ret;

    if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/upTrade") == 0)
    {
        /* code */
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/upTradeBatch") == 0)
    {
        /* code */
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/cancelTrade") == 0)
    {
        /* code */
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/cancelTradeBatch") == 0)
    {
        /* code */
    }else
    {
        /* code */
    }
    
    
    return iDataLen;
}

