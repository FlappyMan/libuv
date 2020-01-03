#include "RequestOperMatchData.h"
CRequestOperMatchData::CRequestOperMatchData(CMatchedDataModel model)
{
    m_mMatchData = model;
}
int CRequestOperMatchData::requestOperation(uv_tcp_t *client)
{
    
}