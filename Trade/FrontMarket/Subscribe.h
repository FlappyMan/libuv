
#ifndef _SUBSCRIBE_HEADER_
#define _SUBSCRIBE_HEADER_


#include "UProtocol.h"



class ClientSession;
class Subscribe
{
public:

public:
	string m_id;            // market id

	string m_currency;		// 当前货币种类 (markets)
	string m_depth;		// 深度
	string m_tradelog;		// tradelog
	string m_kline;		// kline 的时间间隔
public:
};

class Market
{
public:
	Market(){};
	~Market(){};
	void Init(string &id){m_id=id;};

	void DepthAdd(ClientSession *p);
	void DepthRemove(ClientSession *p);

	void TraceLogAdd(ClientSession *p);
	void TraceLogRemove(ClientSession *p);

	void KlineAdd(ClientSession *p,KLINE kl);
	void KlineRemove(ClientSession *p,KLINE kl);
public:
	string m_id;

	set<ClientSession*> m_depth;
	set<ClientSession*> m_tracelog;
	set<ClientSession*> m_order;

	set<ClientSession*> m_60s;
	set<ClientSession*> m_5m;
	set<ClientSession*> m_15m;
	set<ClientSession*> m_30m;
	set<ClientSession*> m_1h;
	set<ClientSession*> m_6h;
	set<ClientSession*> m_1d;
	set<ClientSession*> m_1w;
	set<ClientSession*> m_1m;
};


class MarketMgr
{
public:
    MarketMgr();
    ~MarketMgr();

	void Destroy();
	void Init();

	Market* Get(string &id);

	void AddMarket(string &sMarketID);
public:
    map<string,Market*> m_mMarket;
};
extern MarketMgr g_market_mgr;



#endif


