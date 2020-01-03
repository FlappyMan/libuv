#ifndef _MATCH_MODEL_H_
#define _MATCH_MODEL_H_

#include "BackTrade_Marco.h"
class CMatchToDBModel
{
private:
    /* data */
public:
    CMatchToDBModel();
    virtual ~CMatchToDBModel();

public:
    string m_matchId;
};

#endif