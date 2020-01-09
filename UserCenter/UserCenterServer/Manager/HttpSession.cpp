#include "HttpSession.h"
#include "DispatchManager.h"
#include "LoginDto.h"
#include "LoginRespDto.h"
CHttpSession::CHttpSession()
{
    m_buffer.Init(2048);
    m_uiType = 0;
    m_uiValueLen = 0;
    m_bRecvFinish = false;
    m_http.Init(HTTP_REQUEST);
}
CHttpSession::~CHttpSession()
{
}

int CHttpSession::OnRecv(uv_tcp_t *client, char *pBuffer, int iDataLen)
{
    cout << "[CHttpSession OnRecv]" << endl;
    int ret = m_http.Readed(pBuffer, iDataLen);
    if (ret == RET_SUCCESS)
    {
        cout << "[CHttpSession OnRecv IsHeaderComplete]" << endl;
#ifdef DEBUG
        assert(true == m_http.IsHeaderComplete());
#else
        if (true != m_http.IsHeaderComplete())
        {
            return RET_FAILED;
        }
#endif
        if (strcasecmp(m_http.m_sUrl.c_str(), "/api/UserCenter/Login") == 0)
        {
            cout << "[CHttpSession OnRecv HTTP API] = /api/UserCenter/Login" << endl;
            cout << "[CHttpSession OnRecv Body] = " << m_http.m_sBody.c_str() << endl;
            map<string, string>::iterator it = m_http.m_mFiled.find("token");
            if (it != m_http.m_mFiled.end())
            {
                CLoginDto *pLoginDto = new CLoginDto;
                pLoginDto->DeSerialize(m_http.m_sBody.c_str());
                m_http.Destroy();
                m_bRecvFinish = true;
                m_pObject = (CJsonObjectBase *)pLoginDto;
                m_pObject->m_usCMD = 1;
                m_pObject->m_client = client;
                return RET_SUCCESS;
            }
            else
            {
                m_http.Destroy();
                CDispatchManager::DispatchHttpResponse("", client, false);
                return RET_FAILED;
            }
        }
        else
        {
            // 未知接口
            m_http.Destroy();
            CDispatchManager::DispatchHttpResponse("", client, false);
            return RET_FAILED;
        }
    }
    else if (ret > 0)
    {
        cout << "[CHttpSession RET_HOLD]" << endl;
        m_http.Destroy();
        pBuffer[iDataLen] = 0;
        return RET_HOLD;
    }
    else
    {
        cout << "[CHttpSession RET_FAILED]" << endl;
        m_http.Destroy();
        CDispatchManager::DispatchHttpResponse("", client, false);
        return RET_FAILED;
    }
}