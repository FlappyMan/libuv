#include "UBaseSession.h"
#include "BaseRequestOper.h"
#include "RequestOperTrade.h"
#include "RequestOperTradeBatch.h"
#include "RequestOperCancelTrade.h"
#include "RequestOperCancelTradeBatch.h"
#include "RequestOperMatchData.h"
#include "RequestOperResponseData.h"
#include "CancelTradeBatchModel.hpp"
#include "CancelTradeModel.hpp"
#include "MatchedDataModel.hpp"
#include "TradeBatchModel.hpp"
#include "TradeModel.hpp"
#include "ResponseModel.hpp"
CBaseSession::CBaseSession()
{
    m_buffer.Init(2048);
    m_uiValueLen = 0;
    m_usType = 0;
    m_bRecvFinish = false;
}
CBaseSession::~CBaseSession()
{
    cout<<"~CBaseSession"<<endl;
    m_buffer.RemoveData(m_uiValueLen);
}

int CBaseSession::OnRecv(uv_tcp_t *client, char *pBuffer, int iDataLen)
{
    cout << "[CBaseSession]:[OnRecv]" << endl;
    int iTotalDataLen = m_buffer.AppendData(pBuffer, iDataLen);
    int ret = ProtocolHead(m_usType, m_uiValueLen, m_buffer.Data(), m_buffer.DataLength());
    
    if (ret == RET_HOLD)
    {
        cout << "[CBaseSession]:[RET_HOLD]" << endl;
        m_bRecvFinish = true;
        return ret;
    }
    else if (ret == RET_FAILED)
    {
        cout << "[CBaseSession]:[RET_FAILED]" << endl;
        return ret;
    }
    else
    {
        cout << "[CBaseSession]:[RET_SUCCESS]" << endl;
        m_bRecvFinish = true;
        m_client = client;
        return RET_SUCCESS;
    }
}

string CBaseSession::PraseOperation()
{
    string retToken = "";
    UProtocolBase *pkg = NULL;
    CBaseRequestOper *oper = NULL;
    switch (m_usType)
    {
    case UPUptrade::CMD:
    {
        cout << "[UPUptrade]:[CMD]" << endl;
        pkg = new UPUptrade;
        ProtoUnpack(*(UPUptrade *)pkg, m_buffer.Data(), m_uiValueLen);
        CTradeModel model;
        model = (UPUptrade *)pkg;
        oper = new CRequestOperTrade(model);
    }
    break;
    case UPUptradebatch::CMD:
    {
        cout << "[UPUptradebatch]:[CMD]" << endl;
        pkg = new UPUptradebatch;
        ProtoUnpack(*(UPUptradebatch *)pkg, m_buffer.Data(), m_uiValueLen);
        CTradeBatchModel model;
        model = (UPUptradebatch *)pkg;
        oper = new CRequestOperTradeBatch(model);
    }
    break;
    case UPCanceltrade::CMD:
    {
        cout << "[UPCanceltrade]:[CMD]" << endl;
        pkg = new UPCanceltrade;
        ProtoUnpack(*(UPCanceltrade *)pkg, m_buffer.Data(), m_uiValueLen);
        CCancelTradeModel model;
        model = (UPCanceltrade *)pkg;
        oper = new CRequestOperCancelTrade(model);
    }

    break;
    case UPCanceltradebatch::CMD:
    {
        cout << "[UPCanceltradebatch]:[CMD]" << endl;
        pkg = new UPCanceltradebatch;
        ProtoUnpack(*(UPCanceltradebatch *)pkg, m_buffer.Data(), m_uiValueLen);
        CCancelTradeBatchModel model;
        model = (UPCanceltradebatch *)pkg;
        oper = new CRequestOperCancelTradeBatch(model);
    }
    break;
    case UPMatchedData::CMD:
    {
        cout << "[UPMatchedData]:[CMD]" << endl;
        pkg = new UPMatchedData;
        ProtoUnpack(*(UPMatchedData *)pkg, m_buffer.Data(), m_uiValueLen);
        CMatchedDataModel model;
        model = (UPMatchedData *)pkg;
        oper = new CRequestOperMatchData(model);
    }
    break;
    case UPResponse::CMD:
    {
        cout << "[UPResponse]:[CMD]" << endl;
        pkg = new UPResponse;
        ProtoUnpack(*(UPResponse *)pkg, m_buffer.Data(), m_uiValueLen);
        CResponseModel model;
        model = (UPResponse *)pkg;
        oper = new CRequestOperResponseData(model);
    }
    break;
    default:
    {
        cout << "[default]:[" << m_usType << "]" << endl;
    }
    break;
    }
    retToken = oper->getRequestToken();
    m_buffer.RemoveData(m_uiValueLen);
    if (NULL != oper)
    {
        delete oper;
        oper = NULL;
    }
    
    if (NULL != pkg)
    {
        delete pkg;
        pkg = NULL;
    }
    return retToken;
}