#include "BackTradeSession.h"
#include "ThreadBackTrade.h"
#include "BackTradeSrv.h"

BackTradeSession::BackTradeSession(uv_tcp_t *tcp,BackTradeSrv *pSrv):m_tcp(tcp),m_pSrv(pSrv),
	m_bLogined(false),m_bSyncFinished(false)
{

}

BackTradeSession::~BackTradeSession()
{
	Destroy();
}

void BackTradeSession::Destroy()
{
	while(m_qSyncFile.size()>0)
	{
		delete m_qSyncFile.front();
		m_qSyncFile.pop();
	}
}

void BackTradeSession::Init()
{

}

bool BackTradeSession::IsTimeout(time_t tNow)
{
	return tNow > m_tLast+30;
}


// return <0: 协议错误，=0:数据包长度不足，>0:已处理掉的数据长度
int BackTradeSession::Read(char *pBuffer,int iDataLen)
{
	int iTotalDataLen=m_buffer.AppendData(pBuffer,iDataLen);

	uint16_t uiType=0;
	uint32_t uiValueLen=0;

	int ret=0;
	UProtocolBase *pkg=NULL;
	if(m_bLogined==false)
	{
		ret=ProtocolHead(uiType,uiValueLen,m_buffer.Data(),m_buffer.DataLength());
		if(ret<=0)return ret;
		if(uiType!=UPLogin::CMD)return -1;

		UPLogin pkgLogin;
		ProtoUnpack(pkgLogin,m_buffer.Data(),uiValueLen);
		m_buffer.RemoveData(uiValueLen);
		
		// 校验身份
		if(LoginCheck(&pkgLogin)==false)return -1;
		m_bLogined=true;

		// 建立要下载的文件列表
		BuildLoginSyncReq();

		// 发送第一个下载文件的请求
		SendNextSyncReq();

		return uiValueLen;
	}

	while(m_bSyncFinished==false)
	{
		uiType=0;
		uiValueLen=0;
		ret=ProtocolHead(uiType,uiValueLen,m_buffer.Data(),m_buffer.DataLength());
		if(ret<=0)return ret;

		switch (uiType)
		{
		case UPFileData::CMD :
			pkg=new UPFileData;
			ProtoUnpack(*((UPFileData*)pkg),m_buffer.Data(),uiValueLen);
			RecvFileData((UPFileData*)pkg);
			delete pkg;
			break;		
		case UPFileRequest::CMD :
			pkg=new UPFileRequest;
			ProtoUnpack(*((UPFileRequest*)pkg),m_buffer.Data(),uiValueLen);
			RecvFileRequest((UPFileRequest*)pkg);
			delete pkg;
			break;
		}
		m_buffer.RemoveData(uiValueLen);
	}
	if(m_bSyncFinished==false)return ret;

	while(true)
	{
		uiType=0;
		uiValueLen=0;
		ret=ProtocolHead(uiType,uiValueLen,m_buffer.Data(),m_buffer.DataLength());
		if(ret<0)return ret;
		else if(ret==0)break;

		switch (uiType)
		{
		case UPAllmarketinfo::CMD :
			pkg=new UPAllmarketinfo;
			ProtoUnpack(*((UPAllmarketinfo*)pkg),m_buffer.Data(),uiValueLen);
			m_pSrv->AddRequest(pkg);
			break;
		
		case UPKlinedata::CMD :
			pkg=new UPKlinedata;
			ProtoUnpack(*((UPKlinedata*)pkg),m_buffer.Data(),uiValueLen);
			((UPKlinedata*)pkg)->m_sMarketID=m_sMarkID;
			m_pSrv->AddRequest(pkg);
			break;
		
		case UPDepthdata::CMD :
			pkg=new UPDepthdata;
			ProtoUnpack(*((UPDepthdata*)pkg),m_buffer.Data(),uiValueLen);
			((UPDepthdata*)pkg)->m_sMarketID=m_sMarkID;
			m_pSrv->AddRequest(pkg);
			break;

		case UPHistoricalTransactionData::CMD :
			pkg=new UPHistoricalTransactionData;
			ProtoUnpack(*((UPHistoricalTransactionData*)pkg),m_buffer.Data(),uiValueLen);
			((UPHistoricalTransactionData*)pkg)->m_sMarketID=m_sMarkID;
			m_pSrv->AddRequest(pkg);
			break;


		case UPMatchedData::CMD :
			pkg=new UPMatchedData;
			ProtoUnpack(*((UPMatchedData*)pkg),m_buffer.Data(),uiValueLen);
			((UPMatchedData*)pkg)->m_sMarketID=m_sMarkID;
			m_pSrv->AddRequest(pkg);
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
	Json::Value root;
	if(pLogin->ServerCheck(root,m_pSrv->m_sPublicKey)<0)return false;

	// save market
	UPMarketAdd *pMarketAdd=new UPMarketAdd();
	pMarketAdd->m_sMarketID=root["market"].asString();

	if(pMarketAdd->m_sMarketID.length()<=0)
	{
		delete pMarketAdd;
		return false;
	}
	
	m_sMarkID=pMarketAdd->m_sMarketID;

	m_pSrv->AddRequest(pMarketAdd);
	return true;
}

bool BackTradeSession::RecvFileRequest(UPFileRequest *pkg)
{
	if(m_qSyncFile.size()<=0)return false;
	UPFileRequest *req=m_qSyncFile.front();

	if(req->name().compare(pkg->name())!=0 || req->path().compare(pkg->path())!=0)
	{
		return false;
	}

	if(pkg->size()<=pkg->offset() || pkg->modifytime()==req->modifytime())
	{
		delete req;
		m_qSyncFile.pop();
		return true;		// 如果偏移已经等于文件大小，返回
	}

	req->set_size(pkg->size());
	req->set_modifytime(pkg->modifytime());

	return true;
}


bool BackTradeSession::RecvFileData(UPFileData *pkg)
{
	if(m_qSyncFile.size()<=0)return false;
	UPFileRequest *req=m_qSyncFile.front();

	if(req->name().compare(pkg->name())!=0 || req->path().compare(pkg->path())!=0)
	{
		return false;
	}

	if(req->offset()!=pkg->offset())
	{
		return false;
	}
	req->set_offset(pkg->offset()+pkg->length());

	// write data to file
	string sFullPath=g_config.m_sKLineDataDir + req->path();
	FILE *fp=fopen(sFullPath.c_str(),"a+");
	if(fp!=NULL)
	{
		fseek(fp,req->offset(),SEEK_SET);
		fwrite(pkg->data().data(),1,pkg->length(),fp);
		fclose(fp);
	}

	// 请求下载下一个文件
	if(req->offset()>=req->size())
	{
		delete req;
		m_qSyncFile.pop();
		SendNextSyncReq();
	}
}

void BackTradeSession::SendNextSyncReq()
{
	if(m_qSyncFile.size()<=0)
	{
		m_bSyncFinished=true;
		return;
	}

	// send next send request
	UPFileRequest *pkg=NULL;
	while(true)
	{
		pkg=m_qSyncFile.front();
		if(BackTrade_Write<UPFileRequest>((uv_stream_t*)m_tcp, pkg, SIZE_BUFFER_2k)<0)
		{
			delete pkg;
			m_qSyncFile.pop();
			continue;
		}
		break;
	}
}


void BackTradeSession::BuildLoginSyncReq()
{
	string sKLineDataDir=g_config.m_sKLineDataDir+m_sMarkID+"/";

	// 起始时间
	enum{YEAR_BEGIN=2020};
	struct tm _tm;
	_tm.tm_hour=0;
	_tm.tm_min=0;
	_tm.tm_sec=0;
	_tm.tm_isdst=0;
	_tm.tm_year=YEAR_BEGIN-1900;
	_tm.tm_mon=1;
	_tm.tm_mday=1;
	time_t tBegin=mktime(&_tm);


	// 当前时间
	time_t tNow=time(NULL);
	struct tm _tmNow;
	localtime_r(&tNow,&_tmNow);

	// 循环判断所有文件是否已经加载
	int iSyncYear=0;
	time_t tLoop=0;
	UBDate ubDate(_tmNow.tm_year+1900,_tmNow.tm_mon,_tmNow.tm_mday);
	while(true)
	{
		_tm.tm_year=ubDate.Year();
		_tm.tm_mon=ubDate.Month();
		_tm.tm_mday=ubDate.Day();
		tLoop=mktime(&_tm);
		if(tLoop<tBegin)break;

		_Sync1Minute(tLoop);
		if(iSyncYear!=ubDate.Year())
		{
			_SyncXMinute(tLoop);
			iSyncYear=ubDate.Year();
		}

		ubDate--;
	}
}

void BackTradeSession::_Sync1Minute(time_t tCur)
{
	string sFileName;
	UPDir::KLineFileName(sFileName,TIME_GAP_1_MINUTE,tCur);

	string sRoot=UPDIR_KLINE_DIR_ROOT;
	string sRelativePath;
	UPDir::KLineFilePath(sRelativePath,sRoot,TIME_GAP_1_MINUTE,tCur);

	UPFileRequest *pReq=new UPFileRequest;
	pReq->set_name(sFileName);
	pReq->set_path(sRelativePath);
	_SyncFileInfo(pReq);
	m_qSyncFile.push(pReq);
}


void BackTradeSession::_SyncXMinute(time_t tCur)
{
	// 5 分钟
	string sRoot=UPDIR_KLINE_DIR_ROOT;
	string sFileName,sRelativePath;
	UPDir::KLineFileName(sFileName,TIME_GAP_5_MINUTE,tCur);
	UPDir::KLineFilePath(sRelativePath,sRoot,TIME_GAP_5_MINUTE,tCur);
	UPFileRequest *pReq=new UPFileRequest;
	pReq->set_name(sFileName);
	pReq->set_path(sRelativePath);
	_SyncFileInfo(pReq);
	m_qSyncFile.push(pReq);

	
	// 30 分钟
	UPDir::KLineFileName(sFileName,TIME_GAP_30_MINUTE,tCur);
	UPDir::KLineFilePath(sRelativePath,sRoot,TIME_GAP_30_MINUTE,tCur);
	pReq=new UPFileRequest;
	pReq->set_name(sFileName);
	pReq->set_path(sRelativePath);
	_SyncFileInfo(pReq);
	m_qSyncFile.push(pReq);
	
	
	// 60 分钟
	UPDir::KLineFileName(sFileName,TIME_GAP_1_HOUR,tCur);
	UPDir::KLineFilePath(sRelativePath,sRoot,TIME_GAP_1_HOUR,tCur);
	pReq=new UPFileRequest;
	pReq->set_name(sFileName);
	pReq->set_path(sRelativePath);
	_SyncFileInfo(pReq);
	m_qSyncFile.push(pReq);

	
	// 360 分钟	 （6小时）
	UPDir::KLineFileName(sFileName,TIME_GAP_6_HOUR,tCur);
	UPDir::KLineFilePath(sRelativePath,sRoot,TIME_GAP_6_HOUR,tCur);
	pReq=new UPFileRequest;
	pReq->set_name(sFileName);
	pReq->set_path(sRelativePath);
	_SyncFileInfo(pReq);
	m_qSyncFile.push(pReq);

	// 1440 分钟 	（24小时）
	UPDir::KLineFileName(sFileName,TIME_GAP_24_HOUR,tCur);
	UPDir::KLineFilePath(sRelativePath,sRoot,TIME_GAP_24_HOUR,tCur);
	pReq=new UPFileRequest;
	pReq->set_name(sFileName);
	pReq->set_path(sRelativePath);
	_SyncFileInfo(pReq);
	m_qSyncFile.push(pReq);

}

void BackTradeSession::_SyncFileInfo(UPFileRequest *pReq)
{
	string sRoot=UPDIR_KLINE_DIR_ROOT;

	string sFullPath=g_config.m_sKLineDataDir+pReq->path();
	
	struct stat statFile;
	if(stat(sFullPath.c_str(),&statFile)!=0)
	{
		pReq->set_modifytime(0);
		pReq->set_offset(0);
	}
	else
	{
		pReq->set_modifytime((uint64_t)statFile.st_mtime);
		pReq->set_offset(statFile.st_size);
	}
}

