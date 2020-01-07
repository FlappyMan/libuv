#include "RequestOperMatchData.h"
CRequestOperMatchData::CRequestOperMatchData(CMatchedDataModel model)
{
    m_mMatchData = model;
}
UProtocolBase * CRequestOperMatchData::requestOperation()
{
    cout<<"[CRequestOperMatchData]"<<endl;
    return NULL;
}