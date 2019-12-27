

#ifndef _BACKTRADE_SESSION_HEADER_
#define _BACKTRADE_SESSION_HEADER_

#include "global.h"
#include "BlockQueue.h"

class BackTradeSyncFile
{
public:
	string m_sRelativePath;
	string m_sFileName;
};

class BackTradeSession
{
public:
	BackTradeSession(uv_tcp_t *tcp,BlockQueue<UProtocolBase*> &qReq);
	~BackTradeSession();

	void Init();

	int Read(char *pBuffer,int iDataLen);

	void sendReply(uv_tcp_t* client, UProtocolBase* pkg);
protected:
	bool LoginCheck(UPLogin *pLogin);

protected:
	const uv_tcp_t* m_tcp;
	//queue<UProtocolBase*> &m_qRequest;
	BlockQueue<UProtocolBase*> &m_qRequest;
	map<string, UProtocolBase*> m_qReply;
	UBBuffer m_buffer;

	//queue<UPFileRequest *> m_qSyncFile;
public:
	bool m_bLogined;
	//bool m_bSyncFinished;           // 是否已经完成初始化工作（本地缓存k线数据）
	string m_sMarkID;
};

#endif
