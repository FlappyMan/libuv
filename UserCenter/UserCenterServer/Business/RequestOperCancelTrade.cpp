#include "RequestOperCancelTrade.h"
CRequestOperCancelTrade::CRequestOperCancelTrade(CCancelTradeModel model)
{
    m_mCancelTrade = model;
}
UProtocolBase* CRequestOperCancelTrade::requestOperation()
{
    cout<<"[CRequestOperCancelTrade]"<<endl;
    return NULL;
}