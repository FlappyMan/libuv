#include "ClientSession.h"
#include "ThreadClient.h"

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

void ClientSession::SendPkg(uv_tcp_t* client, UProtocolBase* pkg)
{
    m_tLast = time(NULL);
    switch (pkg->m_uiType)//发送给Server
    {
        case UPUptrade::CMD :
            BackTrade_Write((uv_stream_t *)client, dynamic_cast<UPUptrade *>(pkg), SIZE_BUFFER_2k);
            break;
        case UPUptradebatch::CMD :
            BackTrade_Write((uv_stream_t *)client, dynamic_cast<UPUptradebatch *>(pkg), SIZE_BUFFER_2k);
            break;
        case UPCanceltrade::CMD :
            BackTrade_Write((uv_stream_t *)client, dynamic_cast<UPCanceltrade *>(pkg), SIZE_BUFFER_2k);
            break;
        case UPCanceltradebatch::CMD :
            BackTrade_Write((uv_stream_t *)client, dynamic_cast<UPCanceltradebatch *>(pkg), SIZE_BUFFER_2k);
            break;
        default:
            break;
    }
    delete pkg;
}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int ClientSession::Read(uv_tcp_t* client, char *pBuffer,int iDataLen,BlockQueue<UProtocolBase*> &m_qRequest)
{
    // int iTotalDataLen=m_buffer.AppendData(pBuffer,iDataLen);
    // if(m_http.IsGet() == true)
    // {
    //     cout<<"Http method is GET"<<endl;
    // }
    int ret = m_http.Readed(pBuffer,iDataLen);
    if(ret<0) return -1;
    if(ret>0) return 0;

    UProtocolBase *pkg=NULL;
    string token;
    if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/upTrade") == 0)
    {
        pkg = new UPUptrade;
        m_http.GetFiled(token,"token");  
        dynamic_cast<UPUptrade *>(pkg)->set_token(token); 
        JsonUnpack((UPUptrade *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());          
        m_qRequest.put(pkg);
        Client_Write((uv_stream_t*)client,50,200);
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/upTradeBatch") == 0)
    {
        pkg = new UPUptradebatch;
        m_http.GetFiled(token,"token");  
        dynamic_cast<UPUptradebatch *>(pkg)->set_token(token); 
        JsonUnpack((UPUptradebatch *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());
        m_qRequest.put(pkg);
        Client_Write((uv_stream_t*)client,50,200);
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/cancelTrade") == 0)
    {
        pkg = new UPCanceltrade;
        m_http.GetFiled(token,"token");  
        dynamic_cast<UPCanceltrade *>(pkg)->set_token(token); 
        JsonUnpack((UPCanceltrade *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());
        m_qRequest.put(pkg);
        Client_Write((uv_stream_t*)client,50,200);
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/cancelTradeBatch") == 0)
    {
        pkg = new UPCanceltradebatch;
        m_http.GetFiled(token,"token");  
        dynamic_cast<UPCanceltradebatch *>(pkg)->set_token(token); 
        JsonUnpack((UPCanceltradebatch *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());
        m_qRequest.put(pkg);
        Client_Write((uv_stream_t*)client,50,200);
    }else
    {
        Client_Write((uv_stream_t*)client,50,404);
    }   
    delete pkg;   
    return iDataLen;
}

