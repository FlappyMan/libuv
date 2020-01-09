#include "RequestOperTrade.h"

CRequestOperTrade::CRequestOperTrade(CTradeModel model)
{
    m_mTradeModel = model;
}
UProtocolBase* CRequestOperTrade::requestOperation()
{
#ifdef DEBUG
    cout << "[CTradeModel]:[token]=[" << m_mTradeModel.token << "]" << endl;
    cout << "[CTradeModel]:[paypassword]=[" << m_mTradeModel.paypassword << "]" << endl;
    cout << "[CTradeModel]:[marketid]=[" << m_mTradeModel.marketid << "]" << endl;
    cout << "[CTradeModel]:[price]=[" << m_mTradeModel.price << "]" << endl;
    cout << "[CTradeModel]:[num]=[" << m_mTradeModel.num << "]" << endl;
    cout << "[CTradeModel]:[type]=[" << m_mTradeModel.type << "]" << endl;
    cout << "[CTradeModel]:[main_coin]=[" << m_mTradeModel.main_coin << "]" << endl;
#else
    cout << "[CTradeModel]:[release]" << endl;
#endif

    UPUptrade* up = new UPUptrade;
    up->set_token("123");
    up->set_paypassword("456");
    up->set_marketid(1);
    up->set_price(2);
    up->set_num(3);
    up->set_type(4);
    up->set_main_coin(5);
    UProtocolBase* prot = (UProtocolBase*)up;
    prot->m_uiType = m_usCMD;
    return prot;
}