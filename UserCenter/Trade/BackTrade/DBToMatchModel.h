#ifndef _DBTOMATCH_MODEL_H_
#define _DBTOMATCH_MODEL_H_

#include "BackTrade_Marco.h"
class CDBToMatchModel
{
private:
    /* data */
public:
    CDBToMatchModel();
    virtual ~CDBToMatchModel();

public:
    string m_matchId;
};

#endif