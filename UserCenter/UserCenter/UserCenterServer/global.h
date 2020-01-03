

#ifndef _H_GLOBAL_HEADER_
#define _H_GLOBAL_HEADER_


#include "UProtocol.h"
#include "./BaseConfig/config.h"


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


class ReadCache
{
public:
    ReadCache();
    ~ReadCache();

    void Destroy();
    void Init(int i2kCnt,int i8kCnt,int i16kCnt);

    char* Get(int len);
    void Free(char *p,int len);

protected:
    queue<char*> m_q2k;
    queue<char*> m_q8k;
    queue<char*> m_q16k;

    uint32_t m_ui2kCnt;
    uint32_t m_ui8kCnt;
    uint32_t m_ui16kCnt;

    UBLock m_lock;
};




extern string g_dir_root;       // 程序当前路径
extern Config g_config;
extern WriteReqCache g_cache_write_req;
extern ReadCache g_cache_read;


#endif
