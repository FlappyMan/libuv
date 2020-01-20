

#ifndef _THREAD_CLIENT_HEADER_
#define _THREAD_CLIENT_HEADER_

#include "ClientSrv.h"
#include "ThreadBackTrade.h"

void ThreadClient(void *arg);

extern uv_loop_t g_loop_client;
extern ClientSrv g_srv_client;
extern uint64_t m_uClientID;

void ThreadClient(void *arg);
int GetGMTime(char* szGmtTime);

void Client_cbWrited(uv_write_t* req, int status);
int32_t Client_Write(uv_stream_t* client,UPResponse* pkg,int status);

#endif

