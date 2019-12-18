#include "ThreadTCPOper.h"
#include "DispatchManager.h"
uv_loop_t g_uvLoop;
uv_timer_t g_uvTimer;

void CThreadTCPOper::cbTimer(uv_timer_t *handle)
{
	// queue<UProtocolBase *> qReq;
	// g_srv_backtrade.GetRequest(qReq);
	// g_srv_client.PushRequest(qReq);
}

void CThreadTCPOper::cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	cout << "[Server] New read buffer" << endl;
	buf->base = new char[suggested_size];
	buf->len = suggested_size;
}

void CThreadTCPOper::cbClosed(uv_handle_t *handle)
{
	delete (uv_tcp_t *)handle;
}

void CThreadTCPOper::cbWrited(uv_write_t *req, int status)
{
	if (status < 0)
	{
		cout << "[Server] Write failed" << endl;
	}
	g_cache_write_req.Free((UVWriteReq *)req);
}

void CThreadTCPOper::cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	cout << "[Server] Server begin read" << endl;
	if (nread < 0)
	{
		if (nread != UV_EOF)
			cout << "Read error :" << uv_err_name(nread) << endl;
		uv_close((uv_handle_t *)client, cbClosed);
		uv_stop(&g_uvLoop);
		return;
	}
	else if (nread == 0)
	{
		delete[] buf->base;
		cout << "read noting" << endl;
		return;
	}
	else
	{
		cout << "[Server] readed :" << buf->base << endl;
		CDispatchManager::DispatchClient((uv_tcp_t *)client,buf->base,nread);
	}
}

void CThreadTCPOper::cbNewConnection(uv_stream_t *server, int status)
{
	cout << "[BackTrade] Accept new connection" << endl;
	if (status < 0)
	{
		cout << "[BackTrade] New connection error :" << uv_strerror(status) << endl;
		return;
	}

	uv_tcp_t *client = new uv_tcp_t;
	uv_tcp_init(&g_uvLoop, client);
	if (uv_accept(server, (uv_stream_t *)client) == 0)
	{
		int ret = uv_read_start((uv_stream_t *)client, cbReadBuff, cbRead);
		cout << "[BackTrade] New connection begin read : " << ret << endl;
	}
	else
	{
		cout << "[BackTrade] New connection accept failed" << endl;
		uv_close((uv_handle_t *)client, cbClosed);
	}
}

void CThreadTCPOper::ThreadTCPOper(void *arg)
{
	uv_loop_init(&g_uvLoop);
	uv_tcp_t server;
	uv_tcp_init(&g_uvLoop, &server);

	struct sockaddr_in addr;
	uv_ip4_addr(Config::g_sListenIP.c_str(), Config::g_uiListenPort, &addr);

	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
	int ret = uv_listen((uv_stream_t *)&server, 1000, cbNewConnection);
	if (ret)
	{
		cout << "[Client] Listen error :" << uv_strerror(ret) << endl;
		return;
	}

	uv_timer_init(&g_uvLoop, &g_uvTimer);
	uv_timer_start(&g_uvTimer, cbTimer, 10, 1);

	uv_run(&g_uvLoop, UV_RUN_DEFAULT);
}
