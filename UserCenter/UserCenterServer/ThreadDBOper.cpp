#include "ThreadDBOper.h"
#include "DispatchManager.h"
#include "BaseRequestOper.h"
uv_loop_t g_uvDBLoop;
uv_timer_t g_uvDBTimer;
BlockQueue<CBaseRequestOper*> CThreadDBOper::m_qDBOper;
BlockQueue<CDBResult> CThreadDBOper::m_qDBResult;
void CThreadDBOper::cbTimer(uv_timer_t *handle)
{
	while (CThreadDBOper::m_qDBOper.size() != 0)
	{
		CDBResult pResult;
		pResult.m_cOper = CThreadDBOper::m_qDBOper.get();
		pResult.m_cProt = pResult.m_cOper->requestOperation();
		CThreadDBOper::m_qDBResult.put(pResult);
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
