#ifndef _TRADE_REQUESTOPER_HEADER_
#define _TRADE_REQUESTOPER_HEADER_
#include "BaseRequestOper.h"
#include "TradeModel.hpp"

class CRequestOperTrade : public CBaseRequestOper
{
public:
    CRequestOperTrade(CTradeModel model);
    UProtocolBase * requestOperation();
private:
    CTradeModel m_mTradeModel;
};

#endif
