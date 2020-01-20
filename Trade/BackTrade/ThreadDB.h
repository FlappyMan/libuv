#ifndef _THREAD_DB_HEADER_
#define _THREAD_DB_HEADER_

#include "global.h"
#include "UPJsonReflex.hpp"
extern uv_loop_t g_uvDBLoop;
extern uv_timer_t g_uvDBTimer;

class CThreadDB
{
public:
    CThreadDB();
    ~CThreadDB();
    static void ThreadDB(void *arg);
    static void cbTimer(uv_timer_t *handle);
public:

    static UBBlockQueue<CJsonObjectBase> m_qDBBusinessQueue;
    static UBBlockQueue<CJsonObjectBase> m_qDBBusinessResultQueue;
};

#endif
