#include "ThreadHttpOper.h"
#include "DispatchManager.h"
uv_loop_t g_uvHttpLoop;
uv_timer_t g_uvHttpTimer;

void CThreadHttpOper::cbTimer(uv_timer_t *handle)
{
	// queue<UProtocolBase *> qReq;
	// g_srv_backtrade.GetRequest(qReq);
	// g_srv_client.PushRequest(qReq);
}

void CThreadHttpOper::cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	cout << "[CThreadHttpOper->cbNewConnection->cbReadBuff] New read buffer" << endl;
	buf->base = new char[suggested_size];
	buf->len = suggested_size;
}

void CThreadHttpOper::cbClosed(uv_handle_t *handle)
{
	delete (uv_tcp_t *)handle;
}

void CThreadHttpOper::cbWrited(uv_write_t *req, int status)
{
	cout << "[CThreadHttpOper->cbWrited]" << endl;
	if (status < 0)
	{
		cout << "[CThreadHttpOper->cbWrited] Write failed" << endl;
	}
	uv_close((uv_handle_t *)req->handle, cbClosed);
	g_cache_write_req.Free((UVWriteReq *)req);
}

void CThreadHttpOper::cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	cout << "[CThreadHttpOper->cbNewConnection->cbRead] Server begin read" << endl;
	if (nread < 0)
	{
		cout << "[CThreadHttpOper->cbNewConnection->cbRead] nread < 0" << endl;
		if (nread != UV_EOF)
			cout << "[CThreadHttpOper->cbNewConnection->cbRead] Read error :" << uv_err_name(nread) << endl;
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else if (nread == 0)
	{
		cout << "[CThreadHttpOper->cbNewConnection->cbRead] read noting" << endl;
	}
	else
	{
		CDispatchManager::DispatchHttpClient((uv_tcp_t *)client,buf->base,nread);
	}
	delete[] buf->base;
}

void CThreadHttpOper::cbNewConnection(uv_stream_t *server, int status)
{
	cout << "[CThreadHttpOper->cbNewConnection] Accept new connection" << endl;
	if (status < 0)
	{
		cout << "[CThreadHttpOper->cbNewConnection] New connection error :" << uv_strerror(status) << endl;
		return;
	}

	uv_tcp_t *client = new uv_tcp_t;
	uv_tcp_init(&g_uvHttpLoop, client);
	if (uv_accept(server, (uv_stream_t *)client) == 0)
	{
		int ret = uv_read_start((uv_stream_t *)client, cbReadBuff, cbRead);
		cout << "[CThreadHttpOper->cbNewConnection] New connection begin read : " << ret << endl;
	}
	else
	{
		cout << "[CThreadHttpOper->cbNewConnection] New connection accept failed" << endl;
		uv_close((uv_handle_t *)client, cbClosed);
	}
}

void CThreadHttpOper::ThreadHttpOper(void *arg)
{
	cout<<"[CThreadHttpOper Init]"<<endl;
	uv_loop_init(&g_uvHttpLoop);
	uv_tcp_t server;
	uv_tcp_init(&g_uvHttpLoop, &server);

	struct sockaddr_in addr;
	uv_ip4_addr(Config::g_sHttpIP.c_str(), Config::g_uiHttpPort, &addr);

	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
	int ret = uv_listen((uv_stream_t *)&server, 1000, cbNewConnection);
	if (ret)
	{
		cout << "[CThreadHttpOper] Listen error :" << uv_strerror(ret) << endl;
		return;
	}

	uv_timer_init(&g_uvHttpLoop, &g_uvHttpTimer);
	uv_timer_start(&g_uvHttpTimer, cbTimer, 10, 1);

	uv_run(&g_uvHttpLoop, UV_RUN_DEFAULT);
}
