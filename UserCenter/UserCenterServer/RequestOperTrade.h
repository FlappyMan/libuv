#ifndef _TRADE_REQUESTOPER_HEADER_
#define _TRADE_REQUESTOPER_HEADER_
#include "BaseRequestOper.h"
#include "TradeModel.hpp"

class CRequestOperTrade : public CBaseRequestOper
{
public:
    CRequestOperTrade(CTradeModel model);
    int requestOperation(uv_tcp_t *client);
private:
    CTradeModel m_mTradeModel;
};

#endif
