#include "DispatchManager.h"
#include "HttpResp.h"
#include "../ThreadOrder.h"
mapIdxSocket CDispatchManager::g_mapSocketSession;
mapBaseSession CDispatchManager::g_mapTCPSession;

mapIdxSocket CDispatchManager::g_mapUCSocketSession;
mapBaseSession CDispatchManager::g_mapUserCenterSession;
uint64_t CDispatchManager::g_ulOrderIndex = 1;
uint64_t CDispatchManager::g_ulUCIndex = 1;

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
uint64_t CDispatchManager::getSocketMapKey(uv_tcp_t *fd ,mapIdxSocket &mapSockSession)
{
    mapIdxSocket::iterator itr = mapSockSession.find(fd);
#ifdef DEBUG
    assert(itr != mapSockSession.end());
#else
    if (itr != mapSockSession.end())
    {
        return itr->second;
    }
#endif
    return 0;
}

int CDispatchManager::DispatchClient(mapBaseSession &mapSession, mapIdxSocket &mapSockSession,uv_tcp_t *client, char *pBuffer, int iDataLen , uint64_t ulIndex)
{
    mapBaseSession::iterator itr = mapSession.find(CDispatchManager::getSocketMapKey(client, mapSockSession));

    if (itr != mapSession.end())
    {
        return itr->second->OnRecv(client, pBuffer, iDataLen);
    }
    else
    {
        CBaseSession *session = new CBaseSession;
        // socket唯一标识与业务处理对象map
        mapSession.insert(pair<uint64_t, CBaseSession *>(ulIndex, session));
        // 真实socket句柄与socket编号映射map
        mapSockSession.insert(pair<uv_tcp_t *, uint64_t>(client, ulIndex));
        return session->OnRecv(client, pBuffer, iDataLen);
    }
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
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadOrder::cbWrited);
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
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadOrder::cbWrited);
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
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadOrder::cbWrited);
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
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadOrder::cbWrited);
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
        uv_write((uv_write_t *)write, (uv_stream_t *)client, &write->buf, 1, CThreadOrder::cbWrited);
    }
    break;
    default:
        break;
    }
}