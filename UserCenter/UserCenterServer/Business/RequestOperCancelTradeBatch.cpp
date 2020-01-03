#include "RequestOperCancelTradeBatch.h"
CRequestOperCancelTradeBatch::CRequestOperCancelTradeBatch(CCancelTradeBatchModel model)
{
    m_mCancelTradeBatch = model;
}
int CRequestOperCancelTradeBatch::requestOperation(uv_tcp_t *client)
{
    
}