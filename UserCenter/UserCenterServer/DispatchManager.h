#ifndef _DISPATCH_MANAGER_HEADER_
#define _DISPATCH_MANAGER_HEADER_
#include "global.h"
#include "UBaseSession.h"
#include "HttpSession.h"
#include "ThreadTCPOper.h"
#include "ThreadHttpOper.h"


typedef map<uv_tcp_t*,CBaseSession*> mapBaseSession;
typedef map<uv_tcp_t*,CHttpSession*> mapHttpSession;
class CDispatchManager
{
public:
    static int DispatchClient(uv_tcp_t *client, char *pBuffer, int iDataLen);
    static void CloseClient(uv_tcp_t *client);
    static int DispatchOnSend(UProtocolBase *prot,uv_tcp_t *client);

    static int DispatchHttpClient(uv_tcp_t *client, char *pBuffer, int iDataLen);
    static void CloseHttpClient(uv_tcp_t *client);
    static int DispatchHttpResponse(string sResp, uv_tcp_t *client);

public:
    static mapBaseSession g_mapMapping;
    static mapHttpSession g_mapHttpMapping;
};

#endif
