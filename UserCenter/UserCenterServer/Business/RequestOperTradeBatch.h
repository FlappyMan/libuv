#ifndef _TRADEBATCH_REQUESTOPER_HEADER_
#define _TRADEBATCH_REQUESTOPER_HEADER_
#include "BaseRequestOper.h"
#include "TradeBatchModel.hpp"
class CRequestOperTradeBatch : public CBaseRequestOper
{
public:
    CRequestOperTradeBatch(CTradeBatchModel model);
    int requestOperation(uv_tcp_t *client);

public:
    CTradeBatchModel m_mTradeBatch;
};

#endif
