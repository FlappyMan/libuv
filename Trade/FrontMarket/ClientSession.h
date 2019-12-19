

#ifndef _CLIENT_SESSION_HEADER_
#define _CLIENT_SESSION_HEADER_

#include "global.h"
#include "Subscribe.h"

class ClientSession
{
public:
	ClientSession(uv_tcp_t* tcp,char *pBuffer,int iBufferSize);
	~ClientSession();

	void Init();
	void Destroy();
	bool IsTimeout(time_t tNow);

	int Read(char *pBuffer,int iDataLen);

	void SendPkg(UProtocolBase *pkg);

protected:
	int _FrameParse();
	void _Subscribe();
	void _Unsubscribe();
	void _Requst();
	void _Auth();

protected:
	uv_tcp_t * m_tcp;
	UBBuffer m_ubBuffer;
	time_t m_tLast;         // 最后一次读写时间

	UBWsParser m_ws;
	string m_sRequest;			
	char *m_pBuffer;
	int m_iBufferSize;
protected:	
	string m_sClientID;     // 鉴权后会保留用户的 client ids
	
	Subscribe m_subs;	

};

#endif
