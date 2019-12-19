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

            break;
        case UPUptradebatch::CMD :

            break;
        case UPCanceltrade::CMD :

            break;
        case UPCanceltradebatch::CMD :

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

    UProtocolBase *pkg=NULL;
    if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/upTrade") == 0)
    {
        pkg = new UPUptrade;
        for(map<string,string>::iterator it=m_http.m_mFiled.begin();it!=m_http.m_mFiled.end();it++)
        {
            if (strcasecmp(it->first.c_str(), "Token") == 0)
            {
                dynamic_cast<UPUptrade *>(pkg)->set_token(it->second);
            }          
        }   
        JsonUnpack((UPUptrade *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());          
        m_qRequest.put(pkg);
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/upTradeBatch") == 0)
    {
        pkg = new UPUptradebatch;
        for(map<string,string>::iterator it=m_http.m_mFiled.begin();it!=m_http.m_mFiled.end();it++)
        {
            if (strcasecmp(it->first.c_str(), "Token") == 0)
            {
                dynamic_cast<UPUptradebatch *>(pkg)->set_token(it->second);
            }          
        }         
        JsonUnpack((UPUptradebatch *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());
        m_qRequest.put(pkg);
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/cancelTrade") == 0)
    {
        pkg = new UPCanceltrade;
        for(map<string,string>::iterator it=m_http.m_mFiled.begin();it!=m_http.m_mFiled.end();it++)
        {
            if (strcasecmp(it->first.c_str(), "Token") == 0)
            {
                dynamic_cast<UPCanceltrade *>(pkg)->set_token(it->second);
            }          
        }  
        JsonUnpack((UPCanceltrade *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());
        m_qRequest.put(pkg);
    }else if (strcasecmp(m_http.m_sUrl.c_str(),"/api/private/cancelTradeBatch") == 0)
    {
        pkg = new UPCanceltradebatch;
        for(map<string,string>::iterator it=m_http.m_mFiled.begin();it!=m_http.m_mFiled.end();it++)
        {
            if (strcasecmp(it->first.c_str(), "Token") == 0)
            {
                dynamic_cast<UPCanceltradebatch *>(pkg)->set_token(it->second);
            }          
        }  
        JsonUnpack((UPCanceltradebatch *)pkg, (char *)m_http.m_sBody.c_str(), (uint32_t)m_http.m_sBody.length());
        m_qRequest.put(pkg);
    }else
    {
        return -1;
    }         
    return iDataLen;
}

