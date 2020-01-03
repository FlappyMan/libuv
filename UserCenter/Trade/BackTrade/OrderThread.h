#ifndef _ORDER_THREAD_H_
#define _ORDER_THREAD_H_

#include "BackTrade_Marco.h"
#include "Thread.h"
#include "OrderToDBModel.h"
#include "LoadConfig.h"
#include "Log.h"
typedef std::vector<COrderToDBModel> stlVecOrderModel;

/***************************************
* 类名      : COrderThread
* 基类名    : CThread
* author    : Friend.Wu
* 创建日期  : 2019/10/28
****************************************/
class COrderThread : public CThread 
{
public:
	COrderThread();
	virtual ~COrderThread();

public:
	void			Run();
	void 			errorLog(string strFuncName);
public:
	stlVecOrderModel	m_vecOrder;
private:
	CLogger_Debug 		m_Log;
	CLoadConfig			m_config;
};

#endif /* EPOLLTHREAD_H_ */
