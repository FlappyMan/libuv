#ifndef _THREAD_USERCENTER_HEADER_
#define _THREAD_USERCENTER_HEADER_

#include "global.h"
#include "Manager/DispatchManager.h"
extern uv_loop_t g_uvUserCenterLoop;
extern uv_timer_t g_uvUserCenterTimer;

class CThreadUserCenter
{
public:
    CThreadUserCenter();
    ~CThreadUserCenter();
    static void ThreadUserCenter(void *arg);
    static void cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
    static void cbClosed(uv_handle_t *handle);
    static void cbTimer(uv_timer_t *handle);
    static void cbNewConnection(uv_stream_t *server, int status);
    static void cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
    static void cbWrited(uv_write_t *req, int status);
    static void cbConnect(uv_connect_t *req, int status);
    static UBBlockQueue<write_req_t> g_qOrderToUCQueue;
    static UBBlockQueue<write_req_t> g_qOrderToUCRespQueue;
public:
    static mapManagerSession g_mapManager;
    static mapOrderToUCSession g_mapSession;
    static uv_stream_t * fdSocket;
};

#endif
