#include "RequestOperTradeBatch.h"

CRequestOperTradeBatch::CRequestOperTradeBatch(CTradeBatchModel model)
{
    m_mTradeBatch = model;
}
UProtocolBase* CRequestOperTradeBatch::requestOperation()
{
    cout<<"[CRequestOperTradeBatch]"<<endl;
    return NULL;
}