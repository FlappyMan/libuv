#include "RequestOperCancelTrade.h"
CRequestOperCancelTrade::CRequestOperCancelTrade(CCancelTradeModel model)
{
    m_mCancelTrade = model;
}
int CRequestOperCancelTrade::requestOperation(uv_tcp_t *client)
{
    
}