

#ifndef _THREAD_CLIENT_HEADER_
#define _THREAD_CLIENT_HEADER_

#include "ClientSrv.h"
#include "ThreadBackTrade.h"

void ThreadClient(void *arg);

extern uv_loop_t g_loop_client;
extern ClientSrv g_srv_client;

void ThreadClient(void *arg);


void Client_cbWrited(uv_write_t* req, int status);

template<class T>
int32_t Client_Write(uv_stream_t* client,T* pkg,uint32_t uiPkgMaxSize=SIZE_BUFFER_2k) 
{	
	UVWriteReq* req=g_cache_write_req.Get(uiPkgMaxSize);
	if(req==NULL)return -1;

	int ret=ProtoPack<T>(req->buf.base,req->buf.len,*pkg);
	if(ret<=0)
	{
		g_cache_write_req.Free(req);
		return ret;
	}

	req->pkg=pkg;
	uv_write((uv_write_t *)req, client, &req->buf, 1, Client_cbWrited);
};

#endif

