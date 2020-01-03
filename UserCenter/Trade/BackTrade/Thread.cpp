#include "Thread.h"

CThread::CThread()
{
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&m_lock, NULL);
}

CThread::~CThread()
{
	pthread_mutex_destroy(&m_lock);
	// TODO Auto-generated destructor stub
}
// 创建线程
bool CThread::Start()
{
	if (0 == pthread_create(&m_ThreadID, 0, &CThread::ThreadExec, (void *)this))
	{
		return true;
	}
	return false;
}

// 用来执行线程
void *CThread::ThreadExec(void *arg)
{
	CThread *thread = static_cast<CThread *>(arg);
	if (thread != NULL)
	{
		thread->Run();
	}
	exit(1);
	return 0;
}

void CThread::Run()
{
}

void CThread::Join()
{
	pthread_join(m_ThreadID, 0);
}
