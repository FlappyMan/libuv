#ifndef _DISPATCH_MANAGER_HEADER_
#define _DISPATCH_MANAGER_HEADER_
#include "../global.h"
#include "UBaseSession.h"


typedef map<uint64_t,CBaseSession*> mapBaseSession; // socket编号-业务处理对象
typedef map<uv_tcp_t*,uint64_t> mapIdxSocket;   // socket句柄-socket编号
typedef map<string,uint64_t> mapOrderToUCSession;   // token-socket编号
typedef map<uint64_t,write_req_t*> mapManagerSession; // socket编号-发送数据队列
typedef vector<write_req_t*> vecOrderToUSSession;   // 发送数据队列
class CDispatchManager
{
public:
    CDispatchManager();
    ~CDispatchManager();
public:
    static int DispatchClient(mapBaseSession &mapSession, mapIdxSocket &mapSockSession,uv_tcp_t *client, char *pBuffer, int iDataLen , uint64_t ulIndex);
    static int DispatchOnSend(UProtocolBase *prot,uv_tcp_t *client);
    static uint64_t getSocketMapKey(uv_tcp_t *fd ,mapIdxSocket &mapSockSession);
public:
    static mapIdxSocket g_mapSocketSession; // orderThread线程socket-index
    static mapBaseSession g_mapTCPSession;  // orderThread线程index-业务处理对象

    static mapIdxSocket g_mapUCSocketSession; // UCThread线程socket-indx
    static mapBaseSession g_mapUserCenterSession; // UCThread线程indx-业务处理对象

    static UBMysql g_mysql;
    static uint64_t g_ulOrderIndex;
    static uint64_t g_ulUCIndex;
};

#endif
