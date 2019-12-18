#include "RequestOperTradeBatch.h"

int CRequestOperTradeBatch::requestOperation(uv_tcp_t *client)
{
    
}

CRequestOperTradeBatch::CRequestOperTradeBatch(CTradeBatchModel model)
{
    m_mTradeBatch = model;
}