
#include "ThreadClient.h"

uv_timer_t g_timer_client;
uv_loop_t g_loop_client;
ClientSrv g_srv_client;
uint64_t m_uClientID = 0;

void Client_cbTimer(uv_timer_t* handle)
{
    BlockQueue<UProtocolBase*> qReq;
    g_srv_client.GetRequest(qReq);
    g_srv_backtrade.PushRequest(qReq);

    time_t tNow = time(NULL);
    g_srv_client.OnTimer(tNow);
}

void Client_cbClosed(uv_handle_t* handle)
{
    map<uv_tcp_t*,ClientSession*>::iterator it=g_srv_client.m_mSession.find((uv_tcp_t*)handle);
    it->second->Destroy();
    delete it->second;
    g_srv_client.m_mSession.erase(it);
}

void Client_cbReadBuff(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) 
{
    //cout<<"[Server] New read buffer"<<endl;
    suggested_size = SIZE_BUFFER_8k;
    buf->base = g_cache_read.Get(suggested_size);
    buf->len = suggested_size;
}

void Client_cbWrited(uv_write_t* req, int status)
{
    if (status < 0)
    {
        //cout<<"[Server] Write failed"<<endl;
    }
    uv_close((uv_handle_t*)req->handle,Client_cbClosed);
    g_cache_write_req.Free((UVWriteReq*)req);
}

void Client_cbRead(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) 
{
    //cout<<"[Server] Server begin read"<<endl;
    if (nread < 0)
    {
        if (nread != UV_EOF)cout<<"Read error :"<<uv_err_name(nread)<<endl;
        uv_close((uv_handle_t*) client, Client_cbClosed);
        g_cache_read.Free(buf->base,buf->len);
        return;
    }
    if(nread==0)
    {
        //cout<<"read noting"<<endl;
        uv_close((uv_handle_t*) client, Client_cbClosed);
        g_cache_read.Free(buf->base,buf->len);
        return;
    }

    //cout<<"[Server] readed :"<<buf->base<<endl;
    int ret = g_srv_client.Read((uv_tcp_t*)client, buf->base, nread);
    if(ret < 0)
    {
        uv_close((uv_handle_t*) client, Client_cbClosed);
    }
    g_cache_read.Free(buf->base,buf->len);
}


void Client_cbNewConnection(uv_stream_t *server, int status) 
{
    //cout<<"[Client] Accept new connection"<<endl;
    if (status < 0) 
    {
        //cout<<"[Client] New connection error :"<<uv_strerror(status)<<endl;
        return;
    }
    uv_tcp_t *client = new uv_tcp_t;
    uv_tcp_init(&g_loop_client, client);

    if (uv_accept(server, (uv_stream_t*) client) == 0)
    {
        g_srv_client.NewConnection(client);
        int ret=uv_read_start((uv_stream_t*) client, Client_cbReadBuff, Client_cbRead);
        //cout<<"[Client] New connection begin read : "<<ret<<endl;
    }
    else
    {
        //cout<<"[Client] New connection accept failed"<<endl;
        uv_close((uv_handle_t*) client, Client_cbClosed);
    }
}

void ThreadClient(void *arg)
{
    uv_loop_init(&g_loop_client);

    uv_tcp_t server;
    uv_tcp_init(&g_loop_client, &server);

    struct sockaddr_in addr;
    uv_ip4_addr(g_config.m_sListenIP_Client.c_str(), g_config.m_uiListenPort_Client, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int ret = uv_listen((uv_stream_t*) &server, 1000, Client_cbNewConnection);
    if (ret) 
    {
        //cout<<"[Client] Listen error :"<<uv_strerror(ret)<<endl;
        return;
    }

    uv_timer_init(&g_loop_client, &g_timer_client);
    uv_timer_start(&g_timer_client, Client_cbTimer, 10, 1); 

    uv_run(&g_loop_client, UV_RUN_DEFAULT);
}


int GetGMTime(char* szGmtTime)
{   
    if (!szGmtTime)
    {
        return -1;
    }
    struct tm timeInfo;
    time_t cur_time=time(NULL);	
    char szTemp[30] = {0};
    gmtime_r(&cur_time, &timeInfo);  
    strftime(szTemp, sizeof(szTemp), "%a, %d %b %Y %H:%M:%S GMT", &timeInfo);
    strcpy(szGmtTime, szTemp); 
    return 0;
}

int32_t Client_Write(uv_stream_t* client,UPResponse* resPkg,int status) 
{	
    UVWriteReq* req= g_cache_write_req.Get(200);
    if(req==NULL)return -1;
    // UPResponse* resPkg = new UPResponse;//for test
    // if(status == 200)
    // {
    // 	resPkg->set_status(1);
    // 	resPkg->set_data("交易成功!");
    // }else
    // {
    // 	resPkg->set_status(0);
    // 	resPkg->set_data("交易失败!");
    // }
    string sHttpReq;
    if(resPkg && status == 200)
    {
        char buf[50] = {0};
        int ret = JsonPack<UPResponse>(resPkg,buf,50);
        if(ret<=0)
        {
            g_cache_write_req.Free(req);
            uv_close((uv_handle_t*) client, Client_cbClosed);
            return ret;
        }
        string sBody=buf;
        sHttpReq="HTTP/1.1 200 OK\r\n";
        sHttpReq.append("Content-Type: text/html; charset=utf-8\r\n");
        char contentLen[20] = {0};	
        sprintf(contentLen,"Content-Length: %lu\r\n",sBody.length());
        sHttpReq.append(contentLen);
        sHttpReq.append("Content-Language: zh-CN\r\n");
        sHttpReq.append("Connection: Close\r\n");	
        sHttpReq.append("Server: UkexServer\r\n");	
        sHttpReq.append("\r\n");
        sHttpReq.append(sBody);
        delete resPkg;
    }else if(!resPkg && status == 404)
    {
        sHttpReq="HTTP/1.1 404 Not Found\r\n";
        sHttpReq.append("Content-Length: 0\r\n");
        sHttpReq.append("Connection: Close\r\n");	
        sHttpReq.append("Server: UkexServer\r\n");	
    }else
    {
        /*code*/
    }
    req->pkg = resPkg;
    strncpy(req->buf.base,(const char *)sHttpReq.c_str(),sHttpReq.length());
    uv_write((uv_write_t *)req, client, &req->buf, 1, Client_cbWrited);
};
