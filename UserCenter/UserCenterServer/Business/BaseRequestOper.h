#ifndef _BASE_REQUEST_HEADER_
#define _BASE_REQUEST_HEADER_
#include "../global.h"
#include "../Manager/DispatchManager.h"
typedef struct 
{
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

class CBaseRequestOper
{
public:
    virtual UProtocolBase* requestOperation() = 0;
    uint16_t m_usCMD;
    uv_tcp_t *m_client;
};

#endif
