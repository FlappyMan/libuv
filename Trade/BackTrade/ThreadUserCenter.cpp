#include "./Manager/DispatchManager.h"
#include "ThreadUserCenter.h"
uv_loop_t g_uvUserCenterLoop;
uv_timer_t g_uvUserCenterTimer;

UBBlockQueue<write_req_t> CThreadUserCenter::g_qOrderToUCQueue;
UBBlockQueue<write_req_t> CThreadUserCenter::g_qOrderToUCRespQueue;
mapManagerSession CThreadUserCenter::g_mapManager;
mapOrderToUCSession CThreadUserCenter::g_mapSession;
uv_stream_t *CThreadUserCenter::fdSocket = NULL;

void CThreadUserCenter::cbTimer(uv_timer_t *handle)
{
	if (NULL != CThreadUserCenter::fdSocket)
	{
		int iRequestSize = CThreadUserCenter::g_qOrderToUCQueue.size();
		if (0 != iRequestSize)
		{
			vecOrderToUSSession vecProtBase;
			CThreadUserCenter::g_qOrderToUCQueue.get(vecProtBase, iRequestSize);
			for (int i = 0; i < iRequestSize; i++)
			{
				write_req_t *fdClient = vecProtBase[i];
				CThreadUserCenter::g_mapSession.insert(pair<string, uint64_t>(fdClient->session, fdClient->ulPkgIdx));
				CThreadUserCenter::g_mapManager.insert(pair<uint64_t, write_req_t *>(fdClient->ulPkgIdx, fdClient));

				uv_write((uv_write_t *)fdClient, CThreadUserCenter::fdSocket, &fdClient->buf, 1, CThreadUserCenter::cbWrited);
			}
		}
	}
	if (0 != CDispatchManager::g_mapUserCenterSession.size())
	{
		vecOrderToUSSession vecProtBase;
		for (mapBaseSession::iterator itr = CDispatchManager::g_mapUserCenterSession.begin(); itr != CDispatchManager::g_mapUserCenterSession.end();)
		{
			if (true == itr->second->isRecvFinish())
			{
				write_req_t *req = new write_req_t;
				UBBuffer *recvBuf = itr->second->getRecvBuff();
				req->session = itr->second->PraseOperation();
				mapOrderToUCSession::iterator itrOrToUC = CThreadUserCenter::g_mapSession.find(req->session);
				req->ulPkgIdx = itrOrToUC->second;
				CThreadUserCenter::g_mapSession.erase(itrOrToUC);
				req->buf = uv_buf_init(new char[recvBuf->m_uiDataLen], recvBuf->m_uiDataLen);
				memcpy(req->buf.base, recvBuf->m_pBuffer, recvBuf->m_uiDataLen);
				vecProtBase.push_back(req);
			}
			itr++;
		}
		if (0 != vecProtBase.size())
		{
			CThreadUserCenter::g_qOrderToUCRespQueue.put(vecProtBase);
		}
	}
}

void CThreadUserCenter::cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
#ifdef PRINT_LOG
	cout << "[CThreadUserCenter->cbNewConnection->cbReadBuff] Malloc Buffer" << endl;
#endif
	buf->base = new char[suggested_size];
	buf->len = suggested_size;
}

void CThreadUserCenter::cbClosed(uv_handle_t *handle)
{
	delete (uv_tcp_t *)handle;
}

void CThreadUserCenter::cbWrited(uv_write_t *req, int status)
{
#ifdef PRINT_LOG
	cout << "[CThreadUserCenter->cbWrited]" << endl;
#endif
	if (status < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadUserCenter->cbWrited] Write failed" << endl;
#endif
	}
	write_req_t *reqt = (write_req_t *)req;
	mapManagerSession::iterator itr = CThreadUserCenter::g_mapManager.find(reqt->ulPkgIdx);
#ifdef DEBUG
	assert(itr != CThreadUserCenter::g_mapManager.end());
	delete itr->second->buf.base;
	if (itr->second)
	{
		delete itr->second;
		itr->second = NULL;
	}
	CThreadUserCenter::g_mapManager.erase(itr);
#else
	if (itr != CThreadUserCenter::g_mapManager.end())
	{
		delete itr->second->buf.base;
		if (itr->second)
		{
			delete itr->second;
			itr->second = NULL;
		}
		CThreadUserCenter::g_mapManager.erase(itr);
	}
#endif
	int ret = uv_read_start((uv_stream_t *)req->handle, cbReadBuff, cbRead);
#ifdef PRINT_LOG
	cout << "[CThreadUserCenter->CThreadUserCenter::uv_read_start] " << ret << endl;
#endif
}

void CThreadUserCenter::cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
#ifdef PRINT_LOG
	cout << "[CThreadUserCenter->cbNewConnection->cbRead] Server begin read" << endl;
#endif
	if (nread < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadUserCenter->cbNewConnection->cbRead] socket disconnect" << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else if (nread == 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadUserCenter->cbNewConnection->cbRead] read noting" << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else
	{
		int iOperRet = CDispatchManager::DispatchClient(CDispatchManager::g_mapUserCenterSession, CDispatchManager::g_mapUCSocketSession, (uv_tcp_t *)client, buf->base, nread, CDispatchManager::g_ulUCIndex++);
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
			mapBaseSession::iterator itr = CDispatchManager::g_mapUserCenterSession.find(CDispatchManager::getSocketMapKey((uv_tcp_t *)client, CDispatchManager::g_mapUCSocketSession));
			if (itr != CDispatchManager::g_mapUserCenterSession.end())
			{
				if (NULL != itr->second)
				{
					delete itr->second;
					itr->second = NULL;
				}
				CDispatchManager::g_mapUserCenterSession.erase(itr);
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
	cout << "[CThreadUserCenter::cbRead] delete[] buf->base" << endl;
#endif
	delete[] buf->base;
}

void CThreadUserCenter::cbConnect(uv_connect_t *req, int status)
{
	cout << "[CThreadUserCenter::cbConnect] = " << uv_strerror(status) << endl;
#ifdef DEBUG
	assert(status == 0);
	CThreadUserCenter::fdSocket = (uv_stream_t *)req->handle;
#else
	if (status == 0)
	{
		CThreadUserCenter::fdSocket = (uv_stream_t *)req->handle;
	}
#endif
}

void CThreadUserCenter::ThreadUserCenter(void *arg)
{
	cout << "[CThreadUserCenter Init]" << endl;
	uv_loop_init(&g_uvUserCenterLoop);

	uv_tcp_t *server = new uv_tcp_t;
	uv_tcp_init(&g_uvUserCenterLoop, server);
	uv_connect_t *connect = new uv_connect_t;
	struct sockaddr_in addr;
	uv_ip4_addr(Config::g_sUserCenterIP.c_str(), Config::g_uiUserCenterPort, &addr);

	int ret = uv_tcp_connect(connect, server, (const sockaddr *)&addr, cbConnect);
	if (ret)
	{
		cout << "[CThreadUserCenter] Listen error :" << uv_strerror(ret) << endl;
	}
	else
	{
		uv_timer_init(&g_uvUserCenterLoop, &g_uvUserCenterTimer);
		uv_timer_start(&g_uvUserCenterTimer, cbTimer, 10, 1);
		uv_run(&g_uvUserCenterLoop, UV_RUN_DEFAULT);
	}
}
