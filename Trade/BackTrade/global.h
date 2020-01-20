

#ifndef _H_GLOBAL_HEADER_
#define _H_GLOBAL_HEADER_


#include "UProtocol.h"
#include "./BaseConfig/config.h"

// #define PRINT_LOG
#define DEBUG

extern string g_dir_root;       // 程序当前路径
extern Config g_config;
extern WriteReqCache g_cache_write_req;
extern ReadCache g_cache_read;

typedef struct 
{
    uint64_t ulPkgIdx;
    string session;
    uv_write_t *req;
    uv_buf_t buf;
} write_req_t;

#endif
