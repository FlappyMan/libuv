

#ifndef _BACKTRADE_SESSION_HEADER_
#define _BACKTRADE_SESSION_HEADER_

#include "global.h"


class BackTradeSyncFile
{
public:
	string m_sRelativePath;
	string m_sFileName;
};

class BackTradeSession
{
public:
	BackTradeSession(uv_tcp_t *tcp,queue<UProtocolBase*> &qReq);
	~BackTradeSession();

	void Init();

	int Read(char *pBuffer,int iDataLen);
protected:
	bool LoginCheck(UPLogin *pLogin);
	void BuildLoginSyncReq();
	void _Sync1Minute(time_t tCur);
	void _SyncXMinute(time_t tCur);

	void SendNextSyncReq();
	void RecvFileRequest(UPFileRequest *pkg);
	void RecvFileData(UPFileData *pkg);
protected:
	const uv_tcp_t* m_tcp;
	queue<UProtocolBase*> &m_qRequest;
	UBBuffer m_buffer;

	queue<UPFileRequest *> m_qSyncFile;
public:
	bool m_bLogined;
	bool m_bSyncFinished;           // 是否已经完成初始化工作（本地缓存k线数据）
	string m_sMarkID;
};

#endif
