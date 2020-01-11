#include "ThreadTCPOper.h"
#include "DispatchManager.h"
#include "BaseRequestOper.h"
#include "ThreadDBOper.h"
uv_loop_t g_uvLoop;
uv_timer_t g_uvTimer;

void CThreadTCPOper::cbTimer(uv_timer_t *handle)
{
	for (mapBaseSession::iterator itr = CDispatchManager::g_mapMapping.begin(); itr != CDispatchManager::g_mapMapping.end();)
	{
		if (true == itr->second->isRecvFinish())
		{
			CBaseRequestOper *oper = itr->second->PraseOperation();
			CThreadDBOper::m_qDBOper.put(oper);

			delete itr->second;
			itr->second = NULL;
			
			CDispatchManager::g_mapMapping.erase(itr++); // 把数据包从socket接收队列中移除
		}
		else
		{
			itr++;
		}
	}
	
	while (0 != CThreadDBOper::m_qDBResult.size())
	{
		CDBResult *result = CThreadDBOper::m_qDBResult.get();
		CDispatchManager::DispatchOnSend(result->m_cProt,result->m_cOper->m_client);
		if (NULL != result->m_cProt)
		{
			delete result->m_cProt;
			result->m_cProt = NULL;
		}
		if (NULL != result->m_cOper)
		{
			delete result->m_cOper;
			result->m_cOper = NULL;
		}
		
	}
}

void CThreadTCPOper::cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
#ifdef PRINT_LOG
	cout << "[CThreadTCPOper->cbNewConnection->cbReadBuff] New read buffer" << endl;
#endif
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
#ifdef PRINT_LOG
		cout << "[CThreadTCPOper->cbWrited] Write failed" << endl;
#endif
	}
	g_cache_write_req.Free((UVWriteReq *)req);
}

void CThreadTCPOper::cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	cout << "[CThreadTCPOper->cbNewConnection->cbRead] Server begin read" << endl;
	if (nread < 0)
	{
#ifdef DEBUG
		assert (nread != UV_EOF);
#endif
#ifdef PRINT_LOG
		cout << "[CThreadTCPOper->cbNewConnection->cbRead] Read error :" << uv_err_name(nread) << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else if (nread == 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadTCPOper->cbNewConnection->cbRead] read noting" << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else
	{
#ifdef PRINT_LOG
		cout << "[CThreadTCPOper->cbNewConnection->cbRead] readed :" << buf->base << endl;
#endif
		int ret = CDispatchManager::DispatchClient((uv_tcp_t *)client, buf->base, nread);
		if (RET_FAILED == ret)
		{
			mapBaseSession::iterator itr = CDispatchManager::g_mapMapping.find((uv_tcp_t *)client);
			if (itr != CDispatchManager::g_mapMapping.end())
			{
				if (NULL != itr->second)
				{
					delete itr->second;
					itr->second = NULL;
				}
				CDispatchManager::g_mapMapping.erase(itr);
			}
			uv_close((uv_handle_t *)client, cbClosed);
		}
		else if (RET_SUCCESS == ret)
		{
#ifdef PRINT_LOG
			cout << "[CDispatchManager::DispatchClient] socket recv RET_SUCCESS" << endl;
#endif
		}
		else
		{
#ifdef PRINT_LOG
			cout << "[CDispatchManager::DispatchClient] socket recv RET_HOLD" << endl;
#endif
		}
	}
	delete[] buf->base;
}

void CThreadTCPOper::cbNewConnection(uv_stream_t *server, int status)
{
#ifdef PRINT_LOG
	cout << "[CThreadTCPOper->cbNewConnection] Accept new connection" << endl;
#endif
	if (status < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadTCPOper->cbNewConnection] New connection error :" << uv_strerror(status) << endl;
#endif
	}
	else
	{
		uv_tcp_t *client = new uv_tcp_t;
		uv_tcp_init(&g_uvLoop, client);
		if (uv_accept(server, (uv_stream_t *)client) == 0)
		{
			int ret = uv_read_start((uv_stream_t *)client, cbReadBuff, cbRead);
#ifdef PRINT_LOG
			cout << "[CThreadTCPOper->cbNewConnection] New connection begin read : " << ret << endl;
#endif
		}
		else
		{
#ifdef PRINT_LOG
			cout << "[CThreadTCPOper->cbNewConnection] New connection accept failed" << endl;
#endif
			uv_close((uv_handle_t *)client, cbClosed);
		}
	}
}

void CThreadTCPOper::ThreadTCPOper(void *arg)
{
	cout << "[CThreadTCPOper Init]" << endl;
	uv_loop_init(&g_uvLoop);
	uv_tcp_t server;
	uv_tcp_init(&g_uvLoop, &server);

	struct sockaddr_in addr;
	uv_ip4_addr(Config::g_sListenIP.c_str(), Config::g_uiListenPort, &addr);

	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
	int ret = uv_listen((uv_stream_t *)&server, 1000, cbNewConnection);
	if (ret)
	{
		cout << "[CThreadTCPOper Client Listen error]:" << uv_strerror(ret) << endl;
	}
	else
	{
		uv_timer_init(&g_uvLoop, &g_uvTimer);
		uv_timer_start(&g_uvTimer, cbTimer, 10, 1);
		uv_run(&g_uvLoop, UV_RUN_DEFAULT);
	}
}
