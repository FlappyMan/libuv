#ifndef _MATCHDATA_REQUESTOPER_HEADER_
#define _MATCHDATA_REQUESTOPER_HEADER_
#include "BaseRequestOper.h"
#include "MatchedDataModel.hpp"
class CRequestOperMatchData : public CBaseRequestOper
{
public:
    CRequestOperMatchData(CMatchedDataModel model);
    UProtocolBase * requestOperation();

public:
    CMatchedDataModel m_mMatchData;

};

#endif
