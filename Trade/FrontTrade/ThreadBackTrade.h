#ifndef _THREAD_BACKTRADE_HEADER_
#define _THREAD_BACKTRADE_HEADER_

#include "BackTradeSession.h"
#include "BackTradeSrv.h"


void BackTrade_cbWrited(uv_write_t* req, int status);

void ThreadBacktrade(void *arg);
extern uv_loop_t g_loop_backtrade;
extern BackTradeSrv g_srv_backtrade;

#endif

