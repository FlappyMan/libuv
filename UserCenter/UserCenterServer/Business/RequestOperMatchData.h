#ifndef _MATCHDATA_REQUESTOPER_HEADER_
#define _MATCHDATA_REQUESTOPER_HEADER_
#include "BaseRequestOper.h"
#include "MatchedDataModel.hpp"
class CRequestOperMatchData : public CBaseRequestOper
{
public:
    CRequestOperMatchData(CMatchedDataModel model);
    int requestOperation(uv_tcp_t *client);

public:
    CMatchedDataModel m_mMatchData;

};

#endif
