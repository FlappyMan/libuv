#include "ClientSession.h"

ClientSession::ClientSession(uv_tcp_t* tcp,char *pBuffer,int iBufferSize):
	m_tcp(tcp),m_pBuffer(pBuffer),m_iBufferSize(iBufferSize),m_tLast(0)
{
}

ClientSession::~ClientSession()
{

}

void ClientSession::Init()
{
	m_tLast=time(NULL);

	m_ws.Init(HTTP_REQUEST);
}

void ClientSession::Destroy()
{
	m_ws.Destroy();
}

bool ClientSession::IsTimeout(time_t tNow)
{
	return tNow > m_tLast+30;
}

void ClientSession::SendPkg(UProtocolBase *pkg)
{
	m_tLast=time(NULL);

	switch(pkg->m_uiType)
	{
		case UPKlinedata::CMD :
			_SendPkg_KLine((UPKlinedata*)pkg);
			break;
		case UPAllmarketinfo::CMD :
			_SendPkg_AllMarketInfo((UPAllmarketinfo*)pkg);
			break;
		case UPDepthdata::CMD : 
			_SendPkg_DepthData((UPDepthdata*)pkg);
			break;
		case UPMatchedData::CMD :
			_SendPkg_MatchedDat((UPMatchedData*)pkg);
			break;
		default:
			break;
	}
}


void ClientSession::_SendPkg_KLine(UPKlinedata *pkg)
{

}

void ClientSession::_SendPkg_AllMarketInfo(UPAllmarketinfo *pkg)
{

}

void ClientSession::_SendPkg_DepthData(UPDepthdata *pkg)
{

}

void ClientSession::_SendPkg_MatchedDat(UPMatchedData *pkg)
{

}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int ClientSession::Read(char *pBuffer,int iDataLen)
{
	int iTotalDataLen=m_ubBuffer.AppendData(pBuffer,iDataLen);

	int ret=m_ws.Readed(pBuffer,iDataLen);
	if(ret<0)return -1;
	if(ret>0)return ret;

	if(m_ws.IsWebSocket())
	{
		m_sRequest.append(pBuffer,iDataLen);
		ret=_FrameParse();
		if(ret<=0)return ret;
		else return iDataLen;
	}


	ret=m_ws.Readed(pBuffer,iDataLen);
	if(ret<0)return ret;


	if(m_ws.IsWebSocket() && m_ws.IsHeaderComplete())
	{
		m_sRequest=m_ws.m_sBody;
		ret=_FrameParse();
		if(ret<=0)return ret;
		else return iDataLen;
	}

	
	return iDataLen;
}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int ClientSession::_FrameParse()
{
	UBWsParserFrameType wsft;
	int ret=m_ws.WSGetFrame(&wsft,(uint8_t*)m_pBuffer,m_iBufferSize,(uint8_t*)m_ubBuffer.Data(),m_ubBuffer.DataLength());
	if(ret<=0)return ret;

	m_ubBuffer.RemoveData(ret);
	if(wsft==UBWsParserFrameType::PING_FRAME || wsft==UBWsParserFrameType::PONG_FRAME)return ret;

	Json::Value root;
	if(UBJsonUnpack(root,m_pBuffer,ret)==false)return -1;

	Json::Value::Members m(root.getMemberNames());
	std::vector<string>::iterator it=m.begin();
	if(it==m.end())return -2;

	string &cmd=*it;
	Json::Value &v=root[cmd];
	if(v.type()!=Json::stringValue)return -3;

	string sValue=v.asString();
	if(cmd.compare(UPRequest::CMD_WSAPI)==0)
	{
		_Requst(sValue);
		return ret;
	}
	if(cmd.compare(UPSubscribe::CMD_WSAPI)==0)
	{
		_Subscribe(sValue);
		return ret;
	}
	else if(cmd.compare(UPCancelSubscribe::CMD_WSAPI)==0)
	{
		_Unsubscribe(sValue);
		return ret;	
	}
	else if(cmd.compare(UPOpt::CMD_WSAPI)==0)
	{
		_Opt(sValue);
		return ret;
	}

	return -3;
}

// 订阅请求
void ClientSession::_Subscribe(string &str)
{
	vector<string> v;
	UBStringSplit(v,str,'.');
	if(v.size()<=0)return;

	if(v[0].compare("markets")==0)
	{
		if(v.size()<1)return;
		m_subs.m_currency=CurrencyFromString(v[1]);
	}
	else if(v[0].compare("depth")==0)
	{
		if(v.size()<1)return;
		m_subs.m_depth=MARKETFromString(v[1]);
	}
	else if(v[0].compare("tradelog")==0)
	{
		if(v.size()<1)return;
		m_subs.m_tradelog=MARKETFromString(v[1]);
	}
	else if(v[0].compare("kline")==0)
	{
		if(v.size()<1)return;
		m_subs.m_kline=KLineFromString(v[1]);
	}

}

void ClientSession::_Unsubscribe(string &str)
{
	vector<string> v;
	UBStringSplit(v,str,'.');
	if(v.size()<=0)return;

	if(v[0].compare("markets")==0)
	{
		if(v.size()<1)return;
		m_subs.m_currency=CURRENCY_UNKNOWN;
	}
	else if(v[0].compare("depth")==0)
	{
		if(v.size()<1)return;
		m_subs.m_depth=MARKET_UNKNOWN;
	}
	else if(v[0].compare("tradelog")==0)
	{
		if(v.size()<1)return;
		m_subs.m_tradelog=MARKET_UNKNOWN;
	}
	else if(v[0].compare("kline")==0)
	{
		if(v.size()<1)return;
		m_subs.m_kline=KLINE_UNKNOWN;
	}
}

void ClientSession::_Requst(string &str)
{
	vector<string> v;
	UBStringSplit(v,str,'.');
	if(v.size()!=5)return;


}

void ClientSession::_Opt(string &str)
{

}





