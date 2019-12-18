#include "DBThread.h"

CDBThread::CDBThread()
{
	// TODO Auto-generated constructor stub
	cout << "CDBThread" << endl;
	pthread_mutex_init(&m_mtDBToMatchlock, NULL);  
}

CDBThread::~CDBThread()
{
	// TODO Auto-generated destructor stub
}

void CDBThread::Run()
{
	while (1)
	{
#ifdef DEBUG
		sleep(1);
#else
		usleep(10000);
#endif
		praseOrderThread();
		praseMatchThread();

		CDBToMatchModel obj;
		time_t myt = time(NULL);
		obj.m_matchId = std::to_string(myt);
		pthread_mutex_lock(&m_mtDBToMatchlock);
		m_vecDBToMatch.push_back(obj);
		pthread_mutex_unlock(&m_mtDBToMatchlock);

		// cout<<"CDBThread run = "<<m_pOrderThreadObj->m_vecOrder.size()<< endl;
	}
}
void CDBThread::praseOrderThread(){
	if (m_pOrderThreadObj->m_vecOrder.size() > 0)
	{
		pthread_mutex_lock(&m_pOrderThreadObj->m_lock);
		m_pOrderThreadObj->m_vecOrder.pop_back();
		pthread_mutex_unlock(&m_pOrderThreadObj->m_lock);
	}
}
void CDBThread::praseMatchThread(){
	if (m_pMatchThreadObj->m_stlVecMatch.size() > 0)
	{
		pthread_mutex_lock(&m_pMatchThreadObj->m_lock);
		m_pMatchThreadObj->m_stlVecMatch.pop_back();
		pthread_mutex_unlock(&m_pMatchThreadObj->m_lock);
	}
}
void CDBThread::getOrderThread(COrderThread &orderThreadObj){
	m_pOrderThreadObj = &orderThreadObj;
}
void CDBThread::getMatchThread(CMatchThread &matchThreadObj){
	m_pMatchThreadObj = &matchThreadObj;
}