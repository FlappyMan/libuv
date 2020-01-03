#include "OrderThread.h"
#include "OrderToDBModel.h"

#define LOG_RECORD(value) 		m_Log.Logger_Debug(value)

COrderThread::COrderThread() 
{
	// TODO Auto-generated constructor stub
    cout <<"COrderThread"<<endl;
	m_config.GetConfigParmName("VALUE=");
}

COrderThread::~COrderThread() 
{
	// TODO Auto-generated destructor stub
}

void			COrderThread::Run(){
	while (1)
	{
#ifdef DEBUG
		sleep(1);
#else
		usleep(10000);
#endif
		COrderToDBModel obj;
		time_t myt = time(NULL);
		obj.user_id = std::to_string(myt);
		pthread_mutex_lock(&m_lock);
		m_vecOrder.push_back(obj);
		pthread_mutex_unlock(&m_lock);
		time_t t = time(NULL);
		uint64_t uiOrderNumber = time(&t);
		string timeStr = std::to_string(uiOrderNumber);

		uiOrderNumber = (uiOrderNumber <<= 32) & 0xFFFFFFFF00000000;
		string strOrderNo = std::to_string(uiOrderNumber);
		strOrderNo	+= ';';
		strOrderNo 	+= "Trade/upTrade;c7ecf3fbf2354e54bbff3f4132be681b;c3467ec30bc944539800d34270d5511f;10;1000;10000;1;0";
		LOG_RECORD(strOrderNo.c_str());
	}
}
