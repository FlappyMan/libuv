#include "ThreadHttpOper.h"
#include "./Manager/DispatchManager.h"
#include "ThreadDBOper.h"
#include <vector>
uv_loop_t g_uvHttpLoop;
uv_timer_t g_uvHttpTimer;

void CThreadHttpOper::cbTimer(uv_timer_t *handle)
{
#ifdef ARRAY
	std::vector<CJsonObjectBase *> vecArray;
#endif
	for (mapHttpSession::iterator itr = CDispatchManager::g_mapHttpMapping.begin(); itr != CDispatchManager::g_mapHttpMapping.end();)
	{

		if (true == itr->second->isRecvFinish())
		{
			CJsonObjectBase *pRespOper = itr->second->m_pObject;
#ifdef ARRAY
			vecArray.push_back(pRespOper);
#else
			CThreadDBOper::m_qDBJsonObjOper.put(pRespOper);
#endif
			itr->second->m_pObject = NULL;
			if (NULL != itr->second)
			{
				delete itr->second;
				itr->second = NULL;
			}
			CDispatchManager::g_mapHttpMapping.erase(itr++);
		}
		else
		{
			itr++;
		}
	}
#ifdef ARRAY
	int iVecSize = vecArray.size();
	if (iVecSize != 0)
	{
		CThreadDBOper::m_qDBJsonObjOper.put(vecArray);
	}
#endif

	int iResultSize = CThreadDBOper::m_qDBResultJsonOper.size();
	if (0 != iResultSize)
	{
#ifdef PRINT_LOG
		cout << "[CThreadHttpOper::cbTimer] response iResultSize = " << iResultSize << endl;
#endif

#ifdef ARRAY
		std::vector<CJsonObjectBase *> vecResp;
		CThreadDBOper::m_qDBResultJsonOper.get(vecResp, iResultSize);
		for (int i = 0; i < iResultSize; i++)
		{
			CJsonObjectBase *pResult = vecResp[i];
			cout<<"CDispatchManager::DispatchHttpResponse"<<endl;
			CDispatchManager::DispatchHttpResponse(pResult->Serialize().c_str(), pResult->m_client);
			if (NULL != pResult)
			{
				delete pResult;
				pResult = NULL;
			}
		}
#else
		CJsonObjectBase *pResult = CThreadDBOper::m_qDBResultJsonOper.get();
		CDispatchManager::DispatchHttpResponse(pResult->Serialize().c_str(), pResult->m_client);
		if (NULL != pResult)
		{
			delete pResult;
			pResult = NULL;
		}
#endif
	}
}

void CThreadHttpOper::cbReadBuff(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
#ifdef PRINT_LOG
	cout << "[CThreadHttpOper->cbNewConnection->cbReadBuff] Malloc Buffer" << endl;
#endif
	buf->base = new char[suggested_size];
	buf->len = suggested_size;
}

void CThreadHttpOper::cbClosed(uv_handle_t *handle)
{
	delete (uv_tcp_t *)handle;
}

void CThreadHttpOper::cbWrited(uv_write_t *req, int status)
{
#ifdef PRINT_LOG
	cout << "[CThreadHttpOper->cbWrited]" << endl;
#endif
	if (status < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadHttpOper->cbWrited] Write failed" << endl;
#endif
	}
	uv_close((uv_handle_t *)req->handle, cbClosed);
	g_cache_write_req.Free((UVWriteReq *)req);
}

void CThreadHttpOper::cbRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
#ifdef PRINT_LOG
	cout << "[CThreadHttpOper->cbNewConnection->cbRead] Server begin read" << endl;
#endif
	if (nread < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadHttpOper->cbNewConnection->cbRead] socket disconnect" << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else if (nread == 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadHttpOper->cbNewConnection->cbRead] read noting" << endl;
#endif
		uv_close((uv_handle_t *)client, cbClosed);
	}
	else
	{
		int iOperRet = CDispatchManager::DispatchHttpClient((uv_tcp_t *)client, buf->base, nread);
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
			mapHttpSession::iterator itr = CDispatchManager::g_mapHttpMapping.find((uv_tcp_t *)client);
			if (itr != CDispatchManager::g_mapHttpMapping.end())
			{
				if (NULL != itr->second)
				{
					delete itr->second;
					itr->second = NULL;
				}
				CDispatchManager::g_mapHttpMapping.erase(itr);
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
	cout << "[CThreadHttpOper::cbRead] delete[] buf->base" << endl;
#endif
	delete[] buf->base;
}

void CThreadHttpOper::cbNewConnection(uv_stream_t *server, int status)
{
#ifdef PRINT_LOG
	cout << "[CThreadHttpOper->cbNewConnection] Accept new connection" << endl;
#endif
	if (status < 0)
	{
#ifdef PRINT_LOG
		cout << "[CThreadHttpOper->cbNewConnection] New connection error :" << uv_strerror(status) << endl;
#endif
	}
	else
	{
		uv_tcp_t *client = new uv_tcp_t;
		uv_tcp_init(&g_uvHttpLoop, client);
		if (uv_accept(server, (uv_stream_t *)client) == 0)
		{
			int ret = uv_read_start((uv_stream_t *)client, cbReadBuff, cbRead);
#ifdef PRINT_LOG
			cout << "[CThreadHttpOper->cbNewConnection] New connection begin read : " << ret << endl;
#endif
		}
		else
		{
#ifdef PRINT_LOG
			cout << "[CThreadHttpOper->cbNewConnection] New connection accept failed" << endl;
#endif
			uv_close((uv_handle_t *)client, cbClosed);
		}
	}
}

void CThreadHttpOper::ThreadHttpOper(void *arg)
{
	cout << "[CThreadHttpOper Init]" << endl;
	uv_loop_init(&g_uvHttpLoop);
	uv_tcp_t server;
	uv_tcp_init(&g_uvHttpLoop, &server);

	struct sockaddr_in addr;
	uv_ip4_addr(Config::g_sHttpIP.c_str(), Config::g_uiHttpPort, &addr);

	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
	int ret = uv_listen((uv_stream_t *)&server, 5000, cbNewConnection);
	if (ret)
	{
		cout << "[CThreadHttpOper] Listen error :" << uv_strerror(ret) << endl;
	}
	else
	{
		uv_timer_init(&g_uvHttpLoop, &g_uvHttpTimer);
		uv_timer_start(&g_uvHttpTimer, cbTimer, 10, 1);
		uv_run(&g_uvHttpLoop, UV_RUN_DEFAULT);
	}
}
