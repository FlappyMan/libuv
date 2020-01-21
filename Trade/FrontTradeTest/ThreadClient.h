

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
template<class T>
int32_t Client_Write(uv_tcp_t* client,T* resPkg,int status) 
{	
    UVWriteReq* req= g_cache_write_req.Get(SIZE_BUFFER_2k);
    if(req==NULL)return -1;
    char s_time[60] = {0};
    GetGMTime(s_time);
    string sHttpReq;
    if(resPkg && status == 200)
    {
        char buf[SIZE_BUFFER_2k] = {0};
        int ret = JsonPack<T>(resPkg,buf,50);
        if(ret<=0)
        {
            g_cache_write_req.Free(req);
            return ret;
        }
        string sBody=buf;
        sHttpReq="HTTP/1.1 200 OK\r\n";
        sHttpReq.append("Content-Type: text/html; charset=utf-8\r\n");
        char date[80] = {0};
        sprintf(date,"Date: %s\r\n",s_time);
        sHttpReq.append(date);
        char contentLen[20] = {0};	
        sprintf(contentLen,"Content-Length: %lu\r\n",sBody.length());
        sHttpReq.append(contentLen);
        sHttpReq.append("Content-Language: zh-CN\r\n");
        sHttpReq.append("Connection: Close\r\n");	
        sHttpReq.append("Server: UkexServer\r\n");	
        sHttpReq.append("\r\n");
        sHttpReq.append(sBody);
    }else
    {
        sHttpReq="HTTP/1.1 404 Not Found\r\n";
        sHttpReq.append("Content-Length: 0\r\n");
        sHttpReq.append("Connection: Close\r\n");	
        sHttpReq.append("Server: UkexServer\r\n");	
    }
    req->pkg = resPkg;
    req->buf.len = sHttpReq.length();
    strncpy(req->buf.base,(const char *)sHttpReq.c_str(),sHttpReq.length());
    uv_write((uv_write_t *)req, (uv_stream_t*)client, &req->buf, 1, Client_cbWrited);
};


#endif

