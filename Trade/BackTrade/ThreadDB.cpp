#include "ThreadDB.h"
#include "DispatchManager.h"
uv_loop_t g_uvDBLoop;
uv_timer_t g_uvDBTimer;

UBBlockQueue<CJsonObjectBase> CThreadDB::m_qDBBusinessQueue;
UBBlockQueue<CJsonObjectBase> CThreadDB::m_qDBBusinessResultQueue;

void CThreadDB::cbTimer(uv_timer_t *handle)
{
	
}

void CThreadDB::ThreadDB(void *arg)
{
	cout << "[CThreadDB Init]" << endl;
	// uv_loop_init(&g_uvDBLoop);
	// uv_timer_init(&g_uvDBLoop, &g_uvDBTimer);
	// uv_timer_start(&g_uvDBTimer, cbTimer, 10, 1);
	// uv_run(&g_uvDBLoop, UV_RUN_DEFAULT);
}
