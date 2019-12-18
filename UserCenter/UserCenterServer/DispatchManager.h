#ifndef _DISPATCH_MANAGER_HEADER_
#define _DISPATCH_MANAGER_HEADER_
#include "global.h"
#include "UBaseSession.h"
#include "ThreadTCPOper.h"
// #include "UProtocol.h"

typedef map<uv_tcp_t*,CBaseSession*> mapBaseSession;
class CDispatchManager
{
public:
    static int DispatchClient(uv_tcp_t *client, char *pBuffer, int iDataLen);
    static void CloseClient(uv_tcp_t *client);
    static int DispatchOnSend(UProtocolBase *prot,uv_tcp_t *client);
public:
    static mapBaseSession g_mapMapping;
};

#endif
