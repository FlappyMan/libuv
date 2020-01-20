#ifndef _THREAD_DB_HEADER_
#define _THREAD_DB_HEADER_

#include "global.h"
#include "./Business/BaseRequestOper.h"

extern uv_loop_t g_uvDBLoop;
extern uv_timer_t g_uvDBTimer;

class CDBResult
{
public:
    CBaseRequestOper *m_cOper;
    UProtocolBase *m_cProt;
};

class CThreadDBOper
{
public:
    CThreadDBOper();
    ~CThreadDBOper();
    static void ThreadDBOper(void *arg);
    static void cbTimer(uv_timer_t *handle);
public:
    static UBBlockQueue<CBaseRequestOper> m_qDBOper;
    static UBBlockQueue<CDBResult> m_qDBResult;

    static UBBlockQueue<CJsonObjectBase> m_qDBJsonObjOper;
    static UBBlockQueue<CJsonObjectBase> m_qDBResultJsonOper;
};

#endif
