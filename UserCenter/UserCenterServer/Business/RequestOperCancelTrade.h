#ifndef _TRADECANCEL_REQUESTOPER_HEADER_
#define _TRADECANCEL_REQUESTOPER_HEADER_
#include "BaseRequestOper.h"
#include "CancelTradeModel.hpp"
class CRequestOperCancelTrade : public CBaseRequestOper
{
public:
    CRequestOperCancelTrade(CCancelTradeModel model);
    int requestOperation(uv_tcp_t *client);
public:
    CCancelTradeModel m_mCancelTrade;
};

#endif
