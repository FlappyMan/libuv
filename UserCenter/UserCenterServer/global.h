

#ifndef _H_GLOBAL_HEADER_
#define _H_GLOBAL_HEADER_


#include "UProtocol.h"
#include "config.h"


class WriteReqCache
{
public:
    WriteReqCache();
    ~WriteReqCache();

    void Destroy();
    void Init(int i2kCnt,int i8kCnt,int i16kCnt);

    UVWriteReq* Get(int iBuffSize);
    void Free(UVWriteReq *p);

protected:
    queue<UVWriteReq*> m_q2k;
    queue<UVWriteReq*> m_q8k;
    queue<UVWriteReq*> m_q16k;

    uint32_t m_ui2kCnt;
    uint32_t m_ui8kCnt;
    uint32_t m_ui16kCnt;
};

extern string g_dir_root;       // 程序当前路径
extern WriteReqCache g_cache_write_req;


#endif
