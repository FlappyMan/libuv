#include "DispatchManager.h"
#include "HttpResp.h"
mapBaseSession CDispatchManager::g_mapMapping;
mapHttpSession CDispatchManager::g_mapHttpMapping;
UBMysql CDispatchManager::g_mysql;
CDispatchManager::CDispatchManager()
{
    CDispatchManager::g_mysql.init(4096);
    bool bConnected = CDispatchManager::g_mysql.Connect(Config::sHost, Config::uiPort, Config::sUser, Config::sPwd, Config::sAccountDB);
    if (bConnected == false)
    {
        string sError;
        CDispatchManager::g_mysql.Error(sError);
        cout << "connect to database failed:" << CDispatchManager::g_mysql.Error() << ":" << sError << endl;
        return;
    }
#ifdef PRINT_LOG
    cout << "connect to database:" << Config::sHost << ":" << Config::uiPort << endl;
#endif
}

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

int CDispatchManager::DispatchHttpClient(uv_tcp_t *client, char *pBuffer, int iDataLen)
{
    mapHttpSession::iterator itr = CDispatchManager::g_mapHttpMapping.find(client);

    if (itr != CDispatchManager::g_mapHttpMapping.end())
    {
        return itr->second->OnRecv(client, pBuffer, iDataLen);
    }
    else
    {
        CHttpSession *session = new CHttpSession;
        CDispatchManager::g_mapHttpMapping.insert(pair<uv_tcp_t *, CHttpSession *>(client, session));
        return session->OnRecv(client, pBuffer, iDataLen);
    }
}

int CDispatchManager::DispatchHttpResponse(string sResp, uv_tcp_t *client, bool success)
{
#ifdef PRINT_LOG
    cout << "[CDispatchManager::DispatchHttpResponse] = " << sResp << endl;
#endif
    string sHttpReq;
    sHttpReq = success == true ? "HTTP/1.1 200 OK \r\n" : "HTTP/1.1 404 Not Found \r\n"; //found API
    sHttpReq.append("Content-Type: text/html; charset=GB2312\r\n");
    sHttpReq.append("Content-Length: 400\r\n");
    sHttpReq.append("Content-Language: zh-CN\r\n");
    sHttpReq.append("Connection: Close\r\n");
    sHttpReq.append("Date: ");
    sHttpReq.append("123123123");
    sHttpReq.append("\r\n");
    sHttpReq.append("Server: UkexServer\r\n");
    sHttpReq.append("\r\n");
    sHttpReq.append(sResp.c_str());

    UVWriteReq *write = g_cache_write_req.Get(sHttpReq.length());
    assert(write != NULL);
    assert(write->buf.base != NULL);
    write->buf.len = sHttpReq.length();
    strncpy(write->buf.base, (const char *)sHttpReq.c_str(), sHttpReq.length());
    uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadHttpOper::cbWrited);
}
int CDispatchManager::DispatchOnSend(UProtocolBase *prot, uv_tcp_t *client)
{
    switch (prot->m_uiType)
    {
    case UPUptrade::CMD:
    {
#ifdef PRINT_LOG
        cout << "[DispatchOnSend]:[UPUptrade]" << endl;
#endif
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
#ifdef PRINT_LOG
        cout << "[DispatchOnSend]:[UPUptradebatch]" << endl;
#endif
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
#ifdef PRINT_LOG
        cout << "[DispatchOnSend]:[UPCanceltrade]" << endl;
#endif
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
#ifdef PRINT_LOG
        cout << "[DispatchOnSend]:[UPCanceltradebatch]" << endl;
#endif
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
#ifdef PRINT_LOG
        cout << "[DispatchOnSend]:[UPMatchedData]" << endl;
#endif
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