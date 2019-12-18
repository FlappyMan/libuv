#ifndef _DB_THREAD_H_
#define _DB_THREAD_H_

#include "BackTrade_Marco.h"
#include "Thread.h"
#include "OrderThread.h"
#include "MatchThread.h"
#include "DBToMatchModel.h"

typedef vector<CDBToMatchModel> vecDBToMactch;
/***************************************
* 类名      : DBThread
* 基类名    : CThread
* author    : Friend.Wu
* 创建日期  : 2019/10/28
****************************************/
class CDBThread : public CThread 
{
private:
	COrderThread 		*m_pOrderThreadObj;
	CMatchThread 		*m_pMatchThreadObj;
	// CSQLDBO 			m_sqlDBO;
public:
	pthread_mutex_t 	m_mtDBToMatchlock;			// 线程互斥锁
	vecDBToMactch 		m_vecDBToMatch;
private:
	void 			praseOrderThread();
	void 			praseMatchThread();
	
public:
	CDBThread();
	virtual ~CDBThread();
	
public:
	void			Run();
	void			getOrderThread(COrderThread &orderThreadObj);
	void			getMatchThread(CMatchThread &matchThreadObj);
};

#endif
