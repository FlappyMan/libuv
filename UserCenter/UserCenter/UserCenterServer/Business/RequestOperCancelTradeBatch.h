#ifndef _TRADECANCELBAT_REQUESTOPER_HEADER_
#define _TRADECANCELBAT_REQUESTOPER_HEADER_
#include "BaseRequestOper.h"
#include "CancelTradeBatchModel.hpp"
class CRequestOperCancelTradeBatch : public CBaseRequestOper
{
public:
    CRequestOperCancelTradeBatch(CCancelTradeBatchModel model);
    int requestOperation(uv_tcp_t *client);
public:
    CCancelTradeBatchModel m_mCancelTradeBatch;
};

#endif
