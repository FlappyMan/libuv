#include "MatchThread.h"
#include "DBThread.h"
CMatchThread::CMatchThread()
{
	// TODO Auto-generated constructor stub
	cout << "CMatchThread" << endl;
}

CMatchThread::~CMatchThread()
{
	// TODO Auto-generated destructor stub
}

void CMatchThread::Run()
{
	while (1)
	{
#ifdef DEBUG
		sleep(1);
#else
		usleep(10000);
#endif
		CMatchToDBModel obj;
		time_t myt = time(NULL);
		obj.m_matchId = std::to_string(myt);
		
		pthread_mutex_lock(&m_lock);
		m_stlVecMatch.push_back(obj);
		pthread_mutex_unlock(&m_lock);

		if (m_pDBThread->m_vecDBToMatch.size() > 0)
		{
			// cout<<"m_vecDBToMatch run = "<<m_pDBThread->m_vecDBToMatch.size()<<endl;
			pthread_mutex_lock(&m_pDBThread->m_mtDBToMatchlock);
			m_pDBThread->m_vecDBToMatch.pop_back();
			pthread_mutex_unlock(&m_pDBThread->m_mtDBToMatchlock);
		}
		else{
			// cout<<"m_vecDBToMatch run 22= "<<m_pDBThread->m_vecDBToMatch.size()<<endl;
		}
	}
}

void CMatchThread::getDBThread(CDBThread& dt)
{
	m_pDBThread =  &dt;
}