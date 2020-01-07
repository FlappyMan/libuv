#include "RequestOperCancelTradeBatch.h"
CRequestOperCancelTradeBatch::CRequestOperCancelTradeBatch(CCancelTradeBatchModel model)
{
    m_mCancelTradeBatch = model;
}
UProtocolBase* CRequestOperCancelTradeBatch::requestOperation()
{
    cout<<"[CRequestOperCancelTradeBatch]"<<endl;
    return NULL;
}