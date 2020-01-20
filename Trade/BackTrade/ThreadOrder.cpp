#include "./Manager/DispatchManager.h"
#include "ThreadOrder.h"
#include "ThreadUserCenter.h"
uv_loop_t g_uvOrderLoop;
uv_timer_t g_uvOrderTimer;

void CThreadOrder::cbTimer(uv_timer_t *handle)
{
	vecOrderToUSSession vecProtBase;
	for (mapBaseSession::iterator itr = CDispatchManager::g_mapTCPSession.begin(); itr != CDispatchManager::g_mapTCPSession.end();)
	{
		if (true == itr->second->isRecvFinish() && false == itr->second->isMoveToUC())
		{
			itr->second->setMoveToUC();
			UBBuffer *recvBuf = itr->second->getRecvBuff();
			write_req_t *req = new write_req_t;
			req->ulPkgIdx = itr->first;
			req->session = itr->second->PraseOperation();
			req->buf = uv_buf_init(new char[recvBuf->m_uiDataLen], recvBuf->m_uiDataLen);
			memcpy(req->buf.base, recvBuf->m_pBuffer, recvBuf->m_uiDataLen);
			vecProtBase.push_back(req);
		}
		itr++;
	}
	if (0 != vecProtBase.size())
	{
		CThreadUserCenter::g_qOrderToUCQueue.put(vecProtBase);
	}

	int iRequestSize = CThreadUserCenter::g_qOrderToUCRespQueue.size();
	if (0 != iRequestSize)
	{
		vecOrderToUSSession vecProtBase;
		CThreadUserCenter::g_qOrderToUCRespQueue.get(vecProtBase, iRequestSize);
		for (int i = 0; i < iRequestSize; i++)
		{
			write_req_t *fdClient = vecProtBase[i];
			mapBaseSession::iterator itr = CDispatchManager::g_mapTCPSession.find(fdClient->ulPkgIdx);
#ifdef DEBUG
			assert(itr != CDispatchManager::g_mapTCPSession.end());
#else
			if (itr == CDispatchManager::g_mapTCPSession.end())
			{
				delete fdClient->buf.base;
				continue;
			}
#endif
			uv_write((uv_write_t *)fdClient, (uv_stream_t *)itr->second->getClientFd(), &fdClient->buf, 1, CThreadUserCenter::cbWrited);
		}
	}
}

void CThreadOrder::cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
#ifdef PRINT_LOG
	cout << "[CThreadOrder->cbNewConnection->cbReadBuff] Malloc Buffer" << endl;
#endif
	buf->base = new char[suggested_size];
	buf->len = suggested_size;
}

void CThreadOrder::cbClosed(uv_handle_t *handle)
{
	delete (uv_tcp_t *)handle;
}

void CThreadOrder::cbWrited(uv_write_t *req, int status)
{
#ifdef PRINT_LOG
	cout << "[CThreadOrder->cbWrited]" << endl;
#endif
	if (status < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadOrder->cbWrited] Write failed" << endl;
#endif
	}
	write_req_t *reqt = (write_req_t *)req;
	mapBaseSession::iterator itr = CDispatchManager::g_mapTCPSession.find(reqt->ulPkgIdx);
#ifdef DEBUG
	assert(itr != CDispatchManager::g_mapTCPSession.end());
#endif
	if (NULL != itr->second)
	{
		delete itr->second;
		itr->second = NULL;
	}
	CDispatchManager::g_mapTCPSession.erase(itr);
}

void CThreadOrder::cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
#ifdef PRINT_LOG
	cout << "[CThreadOrder->cbNewConnection->cbRead] Server begin read" << endl;
#endif
	if (nread < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadOrder->cbNewConnection->cbRead] socket disconnect" << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else if (nread == 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadOrder->cbNewConnection->cbRead] read noting" << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else
	{
		int iOperRet = CDispatchManager::DispatchClient(CDispatchManager::g_mapTCPSession, CDispatchManager::g_mapSocketSession, (uv_tcp_t *)client, buf->base, nread, CDispatchManager::g_ulOrderIndex++);
		if (RET_SUCCESS == iOperRet)
		{
#ifdef PRINT_LOG
			cout << "[CDispatchManager::DispatchHttpClient] socket recv RET_SUCCESS" << endl;
#endif
		}
		else if (RET_FAILED == iOperRet)
		{
#ifdef PRINT_LOG
			cout << "[CDispatchManager::DispatchHttpClient] socket recv RET_FAILED" << endl;
#endif
			mapBaseSession::iterator itr = CDispatchManager::g_mapTCPSession.find(CDispatchManager::getSocketMapKey((uv_tcp_t *)client, CDispatchManager::g_mapSocketSession));
			if (itr != CDispatchManager::g_mapTCPSession.end())
			{
				if (NULL != itr->second)
				{
					delete itr->second;
					itr->second = NULL;
				}
				CDispatchManager::g_mapTCPSession.erase(itr);
			}
			uv_close((uv_handle_t *)client, cbClosed);
		}
		else
		{
#ifdef PRINT_LOG
			cout << "[CDispatchManager::DispatchHttpClient] socket recv RET_HOLD" << endl;
#endif
		}
	}
#ifdef PRINT_LOG
	cout << "[CThreadOrder::cbRead] delete[] buf->base" << endl;
#endif
	delete[] buf->base;
}

void CThreadOrder::cbNewConnection(uv_stream_t *server, int status)
{
#ifdef PRINT_LOG
	cout << "[CThreadOrder->cbNewConnection] Accept new connection" << endl;
#endif
	if (status < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadOrder->cbNewConnection] New connection error :" << uv_strerror(status) << endl;
#endif
	}
	else
	{
		uv_tcp_t *client = new uv_tcp_t;
		uv_tcp_init(&g_uvOrderLoop, client);
		if (uv_accept(server, (uv_stream_t *)client) == 0)
		{
			int ret = uv_read_start((uv_stream_t *)client, cbReadBuff, cbRead);
#ifdef PRINT_LOG
			cout << "[CThreadOrder->cbNewConnection] New connection begin read : " << ret << endl;
#endif
		}
		else
		{
#ifdef PRINT_LOG
			cout << "[CThreadOrder->cbNewConnection] New connection accept failed" << endl;
#endif
			uv_close((uv_handle_t *)client, cbClosed);
		}
	}
}

void CThreadOrder::ThreadOrder(void *arg)
{
	cout << "[CThreadOrder Init]" << endl;
	uv_loop_init(&g_uvOrderLoop);
	uv_tcp_t server;
	uv_tcp_init(&g_uvOrderLoop, &server);
	struct sockaddr_in addr;
	uv_ip4_addr(Config::g_sHttpIP.c_str(), Config::g_uiHttpPort, &addr);

	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
	int ret = uv_listen((uv_stream_t *)&server, 1000, cbNewConnection);
	if (ret)
	{
		cout << "[CThreadOrder] Listen error :" << uv_strerror(ret) << endl;
	}
	else
	{
		uv_timer_init(&g_uvOrderLoop, &g_uvOrderTimer);
		uv_timer_start(&g_uvOrderTimer, cbTimer, 10, 1);
		uv_run(&g_uvOrderLoop, UV_RUN_DEFAULT);
	}
}
