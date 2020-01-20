#include "ThreadDBOper.h"
#include "DispatchManager.h"
#include "BaseRequestOper.h"
uv_loop_t g_uvDBLoop;
uv_timer_t g_uvDBTimer;
UBBlockQueue<CBaseRequestOper> CThreadDBOper::m_qDBOper;
UBBlockQueue<CDBResult> CThreadDBOper::m_qDBResult;
UBBlockQueue<CJsonObjectBase> CThreadDBOper::m_qDBJsonObjOper;
UBBlockQueue<CJsonObjectBase> CThreadDBOper::m_qDBResultJsonOper;

void CThreadDBOper::cbTimer(uv_timer_t *handle)
{
	while (CThreadDBOper::m_qDBOper.size() != 0)
	{
		CDBResult pResult;
		pResult.m_cOper = CThreadDBOper::m_qDBOper.get();
		pResult.m_cProt = pResult.m_cOper->requestOperation();
#ifdef DEBUG
		assert(NULL != pResult.m_cProt);
#else
		if (NULL == pResult.m_cProt)
		{
			continue;
		}
#endif
		CThreadDBOper::m_qDBResult.put(&pResult);
	}

	int iResultSize = CThreadDBOper::m_qDBJsonObjOper.size();
	if (0 != iResultSize)
	{
		std::vector<CJsonObjectBase *> vecResp;
		std::vector<CJsonObjectBase *> vecArray;
		CThreadDBOper::m_qDBJsonObjOper.get(vecResp, iResultSize);
		for (int i = 0; i < iResultSize; i++)
		{
			CJsonObjectBase *pObj = vecResp[i];
			CJsonObjectBase *pResponse = pObj->requestOperation();
			if (NULL != pObj)
			{
				delete pObj;
				pObj = NULL;
			}
#ifdef DEBUG
			assert(NULL != pResponse);
#else
			if (NULL == pResponse)
			{
				continue;
			}
#endif
			vecArray.push_back(pResponse);
		}

		if (vecArray.size() != 0)
		{
			CThreadDBOper::m_qDBResultJsonOper.put(vecArray);
		}
	}
}

void CThreadDBOper::ThreadDBOper(void *arg)
{
	cout << "[CThreadDBOper Init]" << endl;
	uv_loop_init(&g_uvDBLoop);
	uv_timer_init(&g_uvDBLoop, &g_uvDBTimer);
	uv_timer_start(&g_uvDBTimer, cbTimer, 10, 1);
	uv_run(&g_uvDBLoop, UV_RUN_DEFAULT);
}
