#ifndef _THREAD_ORDER_HEADER_
#define _THREAD_ORDER_HEADER_

#include "global.h"

extern uv_loop_t g_uvOrderLoop;
extern uv_timer_t g_uvOrderTimer;

class CThreadOrder
{
public:
    CThreadOrder();
    ~CThreadOrder();
    static void ThreadOrder(void *arg);
    static void cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
    static void cbClosed(uv_handle_t *handle);
    static void cbTimer(uv_timer_t *handle);
    static void cbNewConnection(uv_stream_t *server, int status);
    static void cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
    static void cbWrited(uv_write_t *req, int status);

public:

};

#endif
