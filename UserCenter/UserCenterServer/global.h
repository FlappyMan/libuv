

#ifndef _H_GLOBAL_HEADER_
#define _H_GLOBAL_HEADER_


#include "UProtocol.h"
#include "./BaseConfig/config.h"

#define ARRAY
#define PRINT_LOG

extern string g_dir_root;       // 程序当前路径
extern Config g_config;
extern WriteReqCache g_cache_write_req;
extern ReadCache g_cache_read;


#endif
