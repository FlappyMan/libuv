#ifndef _THREAD_H_
#define _THREAD_H_

#include "BackTrade_Marco.h"
using namespace std;
/***************************************
* 类名      : CThread
* 基类名    : NONE
* author    : W.Y.P
* 创建日期  : 2012/11/09
* 描述      : 线程管理类
****************************************/
class CThread
{
public:
	CThread();
	virtual ~CThread();

public:
	bool		Start();			// 线程开始
	// 重载线程
    virtual void Run();
    void		Join();				// 线程阻塞

protected:
	static void *		ThreadExec(void* arg);	// 线程执行函数
	
public:
	pthread_mutex_t m_lock;			// 线程互斥锁
private:
	pthread_t	m_ThreadID;		// 线程ID
};

#endif /* THREAD_H_ */
