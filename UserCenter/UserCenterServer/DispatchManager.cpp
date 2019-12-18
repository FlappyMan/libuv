#include "DispatchManager.h"

mapBaseSession CDispatchManager::g_mapMapping;
int CDispatchManager::DispatchClient(uv_tcp_t *client, char *pBuffer, int iDataLen)
{
    mapBaseSession::iterator itr = CDispatchManager::g_mapMapping.find(client);

    if (itr != CDispatchManager::g_mapMapping.end())
    {
        return itr->second->OnRecv(client, pBuffer, iDataLen);
    }
    else
    {
        CBaseSession *session = new CBaseSession;
        CDispatchManager::g_mapMapping.insert(pair<uv_tcp_t *, CBaseSession *>(client, session));
        return session->OnRecv(client, pBuffer, iDataLen);
    }
}

void CDispatchManager::CloseClient(uv_tcp_t *client)
{
    mapBaseSession::iterator itr = CDispatchManager::g_mapMapping.find(client);
    if (itr != CDispatchManager::g_mapMapping.end())
    {
        CDispatchManager::g_mapMapping.erase(itr);
    }
}

int CDispatchManager::DispatchOnSend(UProtocolBase *prot, uv_tcp_t *client)
{
    switch (prot->m_uiType)
    {
    case UPUptrade::CMD:
    {
        cout<<"[DispatchOnSend]:[UPUptrade]"<<endl;
        UPUptrade *up = reinterpret_cast<UPUptrade *>(prot);
        const int BUFFSIZE = ProtoPackSize<UPUptrade>(*up);
        char buffer[BUFFSIZE + 1] = {0};
        ProtoPack<UPUptrade>(buffer, BUFFSIZE, *up);
        UVWriteReq *write = g_cache_write_req.Get(BUFFSIZE);
        assert(write != NULL);
        write->pkg = up;
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadTCPOper::cbWrited);
    }
    break;
    case UPUptradebatch::CMD:
    {
        cout<<"[DispatchOnSend]:[UPUptradebatch]"<<endl;
        UPUptradebatch *up = reinterpret_cast<UPUptradebatch *>(prot);
        const int BUFFSIZE = ProtoPackSize<UPUptradebatch>(*up);
        char buffer[BUFFSIZE + 1] = {0};
        ProtoPack<UPUptradebatch>(buffer, BUFFSIZE, *up);
        UVWriteReq *write = g_cache_write_req.Get(BUFFSIZE);
        assert(write != NULL);
        write->pkg = up;
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadTCPOper::cbWrited);
    }
    break;
    case UPCanceltrade::CMD:
    {
        cout<<"[DispatchOnSend]:[UPCanceltrade]"<<endl;
        UPCanceltrade *up = reinterpret_cast<UPCanceltrade *>(prot);
        const int BUFFSIZE = ProtoPackSize<UPCanceltrade>(*up);
        char buffer[BUFFSIZE + 1] = {0};
        ProtoPack<UPCanceltrade>(buffer, BUFFSIZE, *up);
        UVWriteReq *write = g_cache_write_req.Get(BUFFSIZE);
        assert(write != NULL);
        write->pkg = up;
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadTCPOper::cbWrited);
    }
    break;
    case UPCanceltradebatch::CMD:
    {
        cout<<"[DispatchOnSend]:[UPCanceltradebatch]"<<endl;
        UPCanceltradebatch *up = reinterpret_cast<UPCanceltradebatch *>(prot);
        const int BUFFSIZE = ProtoPackSize<UPCanceltradebatch>(*up);
        char buffer[BUFFSIZE + 1] = {0};
        ProtoPack<UPCanceltradebatch>(buffer, BUFFSIZE, *up);
        UVWriteReq *write = g_cache_write_req.Get(BUFFSIZE);
        assert(write != NULL);
        write->pkg = up;
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadTCPOper::cbWrited);
    }
    break;
    case UPMatchedData::CMD:
    {
        cout<<"[DispatchOnSend]:[UPMatchedData]"<<endl;
        UPMatchedData *up = reinterpret_cast<UPMatchedData *>(prot);
        const int BUFFSIZE = ProtoPackSize<UPMatchedData>(*up);
        char buffer[BUFFSIZE + 1] = {0};
        ProtoPack<UPMatchedData>(buffer, BUFFSIZE, *up);
        UVWriteReq *write = g_cache_write_req.Get(BUFFSIZE);
        assert(write != NULL);
        write->pkg = up;
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadTCPOper::cbWrited);
    }
    break;
    default:
        break;
    }
}