#include "ThreadDBOper.h"
#include "DispatchManager.h"
#include "BaseRequestOper.h"
uv_loop_t g_uvDBLoop;
uv_timer_t g_uvDBTimer;
BlockQueue<CBaseRequestOper *> CThreadDBOper::m_qDBOper;
BlockQueue<CDBResult> CThreadDBOper::m_qDBResult;
BlockQueue<CJsonObjectBase *> CThreadDBOper::m_qDBJsonObjOper;
BlockQueue<CJsonObjectBase *> CThreadDBOper::m_qDBResultJsonOper;

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

		CThreadDBOper::m_qDBResult.put(pResult);
	}

	while (CThreadDBOper::m_qDBJsonObjOper.size() != 0)
	{
		CJsonObjectBase* pObj = CThreadDBOper::m_qDBJsonObjOper.get();
		CJsonObjectBase* pResult = pObj->requestOperation();
		cout<<"pObj->requestOperation();"<<endl;
		if (NULL != pObj)
		{
			delete pObj;
			pObj = NULL;
		}
		cout<<"pObj->requestOperation();aaaa"<<endl;
#ifdef DEBUG
		assert(NULL != pResult);
#else
		if (NULL == pResult)
		{
			continue;
		}
#endif
		cout<<"CThreadDBOper::m_qDBResultJsonOper.put"<<endl;
		CThreadDBOper::m_qDBResultJsonOper.put(pResult);
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
