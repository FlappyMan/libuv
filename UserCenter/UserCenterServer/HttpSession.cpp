#include "HttpSession.h"
#include "LoginDto.hpp"
#include "DispatchManager.h"
#include "LoginDto.hpp"
CHttpSession::CHttpSession()
{
    m_buffer.Init(2048);
    m_uiType = 0;
    m_uiValueLen = 0;
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

        UProtocolBase *pkg = NULL;
        string _token;
        map<uv_tcp_t *, UProtocolBase *> temp;
        if (strcasecmp(m_http.m_sUrl.c_str(), "/api/UserCenter/Login") == 0)
        {
            cout << "[CHttpSession OnRecv HTTP API] = /api/UserCenter/Login" <<endl;
            cout << "[CHttpSession OnRecv Body] = " << m_http.m_sBody.c_str() << endl;
            map<string, string>::iterator it = m_http.m_mFiled.find("token");
            if (it != m_http.m_mFiled.end())
            {
                CLoginDto dto;
                dto.DeSerialize(m_http.m_sBody.c_str());
                cout<<"reflax = "<<dto.usercount<<endl;
                cout<<"reflax = "<<dto.password<<endl;
                dto.usercount = "wuyoupengdeces";
                cout<<dto.Serialize().c_str()<<endl;
                cout << "[CHttpSession OnRecv token] = " << it->second << endl;
                for (map<string, string>::iterator it = m_http.m_mFiled.begin(); it != m_http.m_mFiled.end(); it++)
                {
                    if (strcasecmp(it->first.c_str(), "Token") == 0)
                    {
                    }
                }
                m_http.Destroy();
                CDispatchManager::DispatchHttpResponse("{\"token\":\"gdsfdsgfsdg\",\"status\":1,\"deadLine\":\"15901273819\"}", client);
            }
            else
            {
                return RET_FAILED;
            }
        }
        if (pkg != NULL)
        {
            delete pkg;
            pkg = NULL;
        }
        cout << "[CHttpSession RET_SUCCESS]" << endl;
        return RET_SUCCESS;
    }
    else if (ret > 0)
    {
        cout << "[CHttpSession RET_HOLD]" << endl;
        pBuffer[iDataLen] = 0;
        cout << pBuffer << endl;
        return RET_HOLD;
    }
    else
    {
        cout << "[CHttpSession RET_FAILED]" << endl;
        return RET_FAILED;
    }
}