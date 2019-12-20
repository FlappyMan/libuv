#include "BackTradeSession.h"
#include "ThreadBackTrade.h"

BackTradeSession::BackTradeSession(uv_tcp_t *tcp,BlockQueue<UProtocolBase*> &qReq):m_tcp(tcp),m_qRequest(qReq),
	m_bLogined(false),m_bSyncFinished(false)
{

}

BackTradeSession::~BackTradeSession()
{

}

void BackTradeSession::Init()
{

}

// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int BackTradeSession::Read(char *pBuffer,int iDataLen)
{
	int iTotalDataLen=m_buffer.AppendData(pBuffer,iDataLen);

	uint16_t uiType=0;
	uint32_t uiValueLen=0;

	int ret=0;
	UProtocolBase *pkg=NULL;
	// if(m_bLogined==false)
	// {
	// 	ret=ProtocolHead(uiType,uiValueLen,m_buffer.Data(),m_buffer.DataLength());
	// 	if(ret<=0)return ret;
	// 	if(uiType!=UPLogin::CMD)return -1;

	// 	UPLogin pkgLogin;
	// 	ProtoUnpack(pkgLogin,m_buffer.Data(),uiValueLen);
	// 	m_buffer.RemoveData(uiValueLen);
		
	// 	// 校验身份
	// 	if(LoginCheck(&pkgLogin)==false)return -1;
	// 	m_bLogined=true;

	// 	// // 建立要下载的文件列表
	// 	// BuildLoginSyncReq();

	// 	// // 发送第一个下载文件的请求
	// 	// SendNextSyncReq();

	// 	return uiValueLen;
	// }

	// while(m_bSyncFinished==false)
	// {
	// 	uiType=0;
	// 	uiValueLen=0;
	// 	ret=ProtocolHead(uiType,uiValueLen,m_buffer.Data(),m_buffer.DataLength());
	// 	if(ret<=0)return ret;

	// 	switch (uiType)
	// 	{
	// 	case UPFileData::CMD :
	// 		pkg=new UPFileData;
	// 		ProtoUnpack(*((UPFileData*)pkg),m_buffer.Data(),uiValueLen);
	// 		RecvFileData((UPFileData*)pkg);
	// 		break;
		
	// 	case UPFileRequest::CMD :
	// 		pkg=new UPFileRequest;
	// 		ProtoUnpack(*((UPFileRequest*)pkg),m_buffer.Data(),uiValueLen);
	// 		RecvFileRequest((UPFileRequest*)pkg);
	// 		break;
	// 	}
	// 	m_buffer.RemoveData(uiValueLen);
	// }
	// if(m_bSyncFinished==false)return ret;

	while(true)
	{
		uiType=0;
		uiValueLen=0;
		ret=ProtocolHead(uiType,uiValueLen,m_buffer.Data(),m_buffer.DataLength());
		if(ret<0)return ret;
		else if(ret==0)break;

        switch (uiType)
        {
        case UPUptrade::CMD :
            pkg = new UPUptrade;
            ProtoUnpack(*(UPUptrade*)pkg,m_buffer.Data(),uiValueLen);
            m_qRequest.put(pkg);
			m_responsePackage.insert(make_pair(dynamic_cast<UPUptrade*>(pkg)->token(),pkg));
            break;
        case UPUptradebatch::CMD :
            pkg = new UPUptradebatch;
            ProtoUnpack(*(UPUptradebatch*)pkg,m_buffer.Data(),uiValueLen);
            m_qRequest.put(pkg);
			m_responsePackage.insert(make_pair(dynamic_cast<UPUptradebatch*>(pkg)->token(),pkg));          
            break;
        case UPCanceltrade::CMD :
            pkg = new UPCanceltrade;
            ProtoUnpack(*(UPCanceltrade*)pkg,m_buffer.Data(),uiValueLen);
            m_qRequest.put(pkg);
			m_responsePackage.insert(make_pair(dynamic_cast<UPCanceltrade*>(pkg)->token(),pkg));
            break;
        case UPCanceltradebatch::CMD :
            pkg = new UPCanceltradebatch;
            ProtoUnpack(*(UPCanceltradebatch*)pkg,m_buffer.Data(),uiValueLen);
            m_qRequest.put(pkg);
			m_responsePackage.insert(make_pair(dynamic_cast<UPCanceltradebatch*>(pkg)->token(),pkg));
            break;
        default:
            break;
        }
		m_buffer.RemoveData(uiValueLen);
	}

	return iDataLen;
}

bool BackTradeSession::LoginCheck(UPLogin *pLogin)
{
	return true;
}
<<<<<<< HEAD
=======

>>>>>>> refs/remotes/origin/master
// void BackTradeSession::RecvFileRequest(UPFileRequest *pkg)
// {
	
// }


// void BackTradeSession::RecvFileData(UPFileData *pkg)
// {
// 	// write data to file


// 	// file recv finished
// 	SendNextSyncReq();
	
// }

// void BackTradeSession::SendNextSyncReq()
// {
// 	if(m_qSyncFile.size()<=0)
// 	{
// 		m_bSyncFinished=true;
// 		return;
// 	}

// 	// send next send request
// 	UPFileRequest *pkg=NULL;
// 	UVWriteReq* req=NULL;
// 	while(true)
// 	{
// 		pkg=m_qSyncFile.front();
// 		req=g_cache_write_req.Get(SIZE_BUFFER_2k);
// 		if(ProtoPack<UPFileRequest>(req->buf.base,req->buf.len,*pkg)<=0)
// 		{
// 			delete pkg;
// 			m_qSyncFile.pop();

// 			g_cache_write_req.Free(req);
// 			continue;
// 		}
// 		req->pkg=pkg;

// 		uv_write((uv_write_t*) req, (uv_stream_t*)m_tcp, &req->buf, 1, BackTrade_cbWrited);
// 		break;
// 	}
// }


/*

*/

// void BackTradeSession::BuildLoginSyncReq()
// {
// 	string sKLineDataDir=g_config.m_sKLineDataDir+m_sMarkID+"/";

// 	// 起始时间
// 	enum{YEAR_BEGIN=2020};
// 	struct tm _tm;
// 	_tm.tm_hour=0;
// 	_tm.tm_min=0;
// 	_tm.tm_sec=0;
// 	_tm.tm_isdst=0;
// 	_tm.tm_year=YEAR_BEGIN;
// 	_tm.tm_mon=1;
// 	_tm.tm_mday=1;
// 	time_t tBegin=mktime(&_tm);


// 	// 当前时间
// 	time_t tNow=time(NULL);
// 	struct tm _tmNow;
// 	localtime_r(&tNow,&_tmNow);

// 	// 循环判断所有文件是否已经加载
// 	int iSyncYear=0;
// 	time_t tLoop=0;
// 	UBDate ubDate(_tmNow.tm_year+1900,_tmNow.tm_mon,_tmNow.tm_mday);
// 	while(true)
// 	{
// 		_tm.tm_year=ubDate.Year();
// 		_tm.tm_mon=ubDate.Month();
// 		_tm.tm_mday=ubDate.Day();
// 		tLoop=mktime(&_tm);
// 		if(tLoop<tBegin)break;

// 		_Sync1Minute(tLoop);
// 		if(iSyncYear!=ubDate.Year())
// 		{
// 			_SyncXMinute(tLoop);
// 			iSyncYear=ubDate.Year();
// 		}

// 		ubDate--;
// 	}
// }

// void BackTradeSession::_Sync1Minute(time_t tCur)
// {
// 	string sFileName;
// 	UPDir::KLineFileName(sFileName,TIME_GAP_1_MINUTE,tCur);

// 	string sRoot;
// 	string sRelativePath;
// 	UPDir::KLineFilePath(sRelativePath,sRoot,TIME_GAP_1_MINUTE,tCur);

// 	UPFileRequest *pReq=new UPFileRequest;

// 	string sFullPath=g_config.m_sKLineDataDir+sRelativePath;
// 	struct stat statFile;
// 	if(stat(sFullPath.c_str(),&statFile)!=0)
// 	{
// 		pReq->set_modifytime(0);
// 		pReq->set_offset(0);
// 	}
// 	else
// 	{
// 		pReq->set_modifytime((uint64_t)statFile.st_mtime);
// 		pReq->set_offset(statFile.st_size);
// 	}
// 	pReq->set_name(sFileName);
// 	pReq->set_path(sRelativePath);


// 	m_qSyncFile.push(pReq);
// }


// void BackTradeSession::_SyncXMinute(time_t tCur)
// {
// 	string sFullPath=g_config.m_sKLineDataDir;
// 	string sFileName,sFilePath;


// 	// 5 分钟
// 	UPDir::KLineFileName(sFileName,TIME_GAP_1_MINUTE,tCur);
// 	UPDir::KLineFilePath(sFilePath,sFullPath,TIME_GAP_1_MINUTE,tCur);


	
// 	// 30 分钟

	
	
// 	// 60 分钟

	
	
// 	// 360 分钟	 （24小时）



// 	// 1440 分钟 	（24小时）

// }

