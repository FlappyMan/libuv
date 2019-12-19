
#include "ClientSrv.h"

ClientSrv::ClientSrv(int iBufferSize)
{
	uv_mutex_init(&m_lock);

	m_iBufferSize=iBufferSize;
	m_pBuffer=new char[m_iBufferSize];
}

ClientSrv::~ClientSrv()
{

}

void ClientSrv::NewConnection(uv_tcp_t* tcp)
{
	ClientSession *p=new ClientSession(tcp,m_pBuffer,m_iBufferSize);

	m_mSession.insert(make_pair(tcp,p));
}

void ClientSrv::CloseConnection(uv_tcp_t *tcp)
{
	m_mSession.erase(tcp);
}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int ClientSrv::Read(uv_tcp_t* tcp,char *pBuffer,int iDataLen)
{
	map<uv_tcp_t*,ClientSession*>::iterator it=m_mSession.find(tcp);
	if(it==m_mSession.end())return false;

	return it->second->Read(pBuffer,iDataLen);
}


void ClientSrv::PushRequest(queue<UProtocolBase*> &q)
{
	uv_mutex_lock(&m_lock);
	while(q.size()>0)
	{
		m_qReqest.push(q.front());
		q.pop();
	}
	uv_mutex_unlock(&m_lock);
}

void ClientSrv::OnTimer(time_t tNow)
{
	queue<UProtocolBase*> qReq;
	uv_mutex_lock(&m_lock);
	qReq.swap(m_qReqest);
	uv_mutex_unlock(&m_lock);

	map<uv_tcp_t*,ClientSession*>::iterator it;
	UProtocolBase *pkg=NULL;
	while(qReq.size()>0)
	{
		pkg=qReq.front();
		qReq.pop();

		_DispatchPkg(pkg);

		for(it=m_mSession.begin();it!=m_mSession.end();)
		{
			if(it->second->IsTimeout(tNow))
			{
			   it->second->Destroy();
			   
			   delete it->second;
			   it=m_mSession.erase(it);
			   continue;
		   	}

			it->second->SendPkg(pkg);
			it++;
		}
		
		delete pkg;
	}
}


void ClientSrv::_DispatchPkg(UProtocolBase *pkg)
{
	UPAllmarketinfo *pAllMarketInfo=NULL;
	UPKlinedata *pKline=NULL;
	UPDepthdata *pDept=NULL;
	UPHistoricalTransactionData *pHistory=NULL;
	UPMatchedData *pMatchData=NULL;

	switch (pkg->m_uiType)
		{
		case UPAllmarketinfo::CMD :
			
			break;
		
		case UPKlinedata::CMD :
			
			break;
		
		case UPDepthdata::CMD :
			
			break;

		case UPHistoricalTransactionData::CMD :
			
			break;


		case UPMatchedData::CMD :
			
			break;

		default:
			break;
		}
}
