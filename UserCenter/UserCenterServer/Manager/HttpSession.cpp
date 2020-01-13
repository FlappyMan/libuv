#include "HttpSession.h"
#include "DispatchManager.h"
#include "LoginDto.h"
#include "LoginRespDto.h"
CHttpSession::CHttpSession()
{
    m_bRecvFinish = false;
    m_pObject = NULL;
}
CHttpSession::~CHttpSession()
{
}

int CHttpSession::OnRecv(uv_tcp_t *client, char *pBuffer, int iDataLen)
{
#ifdef PRINT_LOG
    cout << "[CHttpSession OnRecv]" << endl;
#endif
    UBHttpParser httpParser;
    httpParser.Init(HTTP_REQUEST);
    int ret = httpParser.Readed(pBuffer, iDataLen);
    if (ret == RET_SUCCESS)
    {
#ifdef PRINT_LOG
        cout << "[CHttpSession OnRecv IsHeaderComplete]" << endl;
#endif

#ifdef DEBUG
        assert(true == httpParser.IsHeaderComplete());
#else
        if (true != httpParser.IsHeaderComplete())
        {
            return RET_FAILED;
        }
#endif
        if (strcasecmp(httpParser.m_sUrl.c_str(), "/api/UserCenter/Login") == 0)
        {
#ifdef PRINT_LOG
            cout << "[CHttpSession OnRecv HTTP API] = /api/UserCenter/Login" << endl;
            cout << "[CHttpSession OnRecv Body] = " << httpParser.m_sBody.c_str() << endl;
#endif
            map<string, string>::iterator it = httpParser.m_mFiled.find("token");
            if (it != httpParser.m_mFiled.end())
            {
                CLoginDto *pLoginDto = new CLoginDto;
                pLoginDto->DeSerialize(httpParser.m_sBody.c_str());
                httpParser.Destroy();
                m_bRecvFinish = true;
#ifdef DEBUG
                assert(m_pObject == NULL);
#endif
                m_pObject = (CJsonObjectBase *)pLoginDto;
                pLoginDto = NULL;
                m_pObject->m_usCMD = 1;
                m_pObject->m_client = client;
                return RET_SUCCESS;
            }
            else
            {
                httpParser.Destroy();
                CDispatchManager::DispatchHttpResponse("", client, false);
                return RET_FAILED;
            }
        }
        else
        {
            // 未知接口
            httpParser.Destroy();
            CDispatchManager::DispatchHttpResponse("", client, false);
            return RET_FAILED;
        }
    }
    else if (ret > 0)
    {
        cout << "[CHttpSession RET_HOLD]" << endl;
        httpParser.Destroy();
        pBuffer[iDataLen] = 0;
        return RET_HOLD;
    }
    else
    {
        cout << "[CHttpSession RET_FAILED]" << endl;
        httpParser.Destroy();
        CDispatchManager::DispatchHttpResponse("", client, false);
        return RET_FAILED;
    }
}