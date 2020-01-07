#include "UBaseSession.h"
#include "RequestOperTrade.h"
#include "RequestOperTradeBatch.h"
#include "RequestOperCancelTrade.h"
#include "RequestOperCancelTradeBatch.h"
#include "RequestOperMatchData.h"
#include "TradeModel.hpp"
#include "TradeBatchModel.hpp"
#include "CancelTradeModel.hpp"
#include "CancelTradeBatchModel.hpp"
#include "MatchedDataModel.hpp"
CBaseSession::CBaseSession()
{
    m_buffer.Init(2048);
    m_uiType = 0;
    m_uiValueLen = 0;
    m_bRecvFinish = false;
}
CBaseSession::~CBaseSession()
{
}
CBaseRequestOper* CBaseSession::PraseOperation()
{
    UProtocolBase *pkg = NULL;
    CBaseRequestOper *oper = NULL;
    switch (m_uiType)
    {
    case UPUptrade::CMD:
    {
        cout << "[UPUptrade]:[CMD]" << endl;
        pkg = new UPUptrade;
        ProtoUnpack(*(UPUptrade *)pkg, m_buffer.Data(), m_uiValueLen);
        CTradeModel model;
        model = (UPUptrade *)pkg;
        oper = new CRequestOperTrade(model);
        // oper->requestOperation(m_client);
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
        // oper->requestOperation(m_client);
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
        // oper->requestOperation(m_client);
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
        // oper->requestOperation(m_client);
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
        // oper->requestOperation(m_client);
    }
    break;
    default:
    {
        cout << "[default]:[" << m_uiType << "]" << endl;
    }
    break;
    }
    oper->m_client = m_client;
    oper->m_usCMD = (uint16_t)m_uiType;
    m_buffer.RemoveData(m_uiValueLen);
    if (NULL != pkg)
    {
        delete pkg;
        pkg = NULL;
    }
    return oper;
}
int CBaseSession::OnRecv(uv_tcp_t *client, char *pBuffer, int iDataLen)
{
    cout << "[CBaseSession]:[OnRecv]" << endl;
    int iTotalDataLen = m_buffer.AppendData(pBuffer, iDataLen);
    int ret = ProtocolHead(m_uiType, m_uiValueLen, m_buffer.Data(), m_buffer.DataLength());
    
    if (ret == RET_HOLD)
    {
        cout << "[CBaseSession]:[RET_HOLD]" << endl;
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