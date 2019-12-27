#include "BackTradeSession.h"
#include "ThreadBackTrade.h"
#include "ThreadClient.h"

BackTradeSession::BackTradeSession(uv_tcp_t *tcp,BlockQueue<UProtocolBase*> &qReq):m_tcp(tcp),m_qRequest(qReq),
	m_bLogined(false)
{

}

BackTradeSession::~BackTradeSession()
{

}

void BackTradeSession::Init()
{

}
void BackTradeSession::sendReply(uv_tcp_t* client, UProtocolBase* pkg)
{
    switch (pkg->m_uiType)
    {
        case UPUptrade::CMD :
        case UPUptradebatch::CMD :
        case UPCanceltrade::CMD :
        case UPCanceltradebatch::CMD :
            //Client_Write((uv_stream_t *)client, dynamic_cast<UPResponse *>(pkg), SIZE_BUFFER_2k);
            break;
        default:
            break;
    }
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

		return uiValueLen;
	}

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
        case UPUptradebatch::CMD :
        case UPCanceltrade::CMD :
        case UPCanceltradebatch::CMD :
            pkg = new UPCanceltradebatch;
            ProtoUnpack(*(UPResponse*)pkg,m_buffer.Data(),uiValueLen);
            m_qRequest.put(pkg);
			m_qReply.insert(make_pair(dynamic_cast<UPResponse*>(pkg)->token(),pkg));//保存来自服务器的Response
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
