#ifndef _MATCH_THREAD_H_
#define _MATCH_THREAD_H_

#include "BackTrade_Marco.h"
#include "Thread.h"
#include "MatchToDBModel.h"

class CDBThread;
typedef std::vector<CMatchToDBModel> stlVecMatchModel;

/***************************************
* 类名      : MatchThread
* 基类名    : CThread
* author    : Friend.Wu
* 创建日期  : 2019/10/28
****************************************/
class CMatchThread : public CThread 
{
public:
	CMatchThread();
	virtual ~CMatchThread();
	
public:
	void			Run();
	void			getDBThread(CDBThread& dt);
public:
	stlVecMatchModel m_stlVecMatch;

private:
	CDBThread		*m_pDBThread;
};

#endif /* EPOLLTHREAD_H_ */
