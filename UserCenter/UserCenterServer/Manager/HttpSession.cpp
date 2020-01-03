#include "HttpSession.h"
#include "LoginDto.hpp"
#include "DispatchManager.h"
#include "LoginDto.hpp"
#include "LoginRespDto.hpp"
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
            cout << "[CHttpSession OnRecv HTTP API] = /api/UserCenter/Login" << endl;
            cout << "[CHttpSession OnRecv Body] = " << m_http.m_sBody.c_str() << endl;
            map<string, string>::iterator it = m_http.m_mFiled.find("token");
            if (it != m_http.m_mFiled.end())
            {
                CLoginDto dto;
                CLoginRespDto respDto;
                dto.DeSerialize(m_http.m_sBody.c_str());
                cout << "reflax = " << dto.usercount << endl;
                cout << "reflax = " << dto.password << endl;
                // cout<<dto.Serialize().c_str()<<endl;
                // cout << "[CHttpSession OnRecv token] = " << it->second << endl;

                // for (map<string, string>::iterator it = m_http.m_mFiled.begin(); it != m_http.m_mFiled.end(); it++)
                // {
                //     if (strcasecmp(it->first.c_str(), "Token") == 0)
                //     {
                //     }
                // }

                // 从表A中查询全部数据，并打印
                string sql = "select id from user where user_account = \"" + dto.usercount + "\" and password = \"" + dto.password + "\"";
                cout << sql << endl;
                bool bHasValue = CDispatchManager::g_mysql.Select(sql);
                if (bHasValue == false)
                {
                    respDto.status = "0";
                }
                else
                {
                    // uint32_t uiResult = 0;
                    // while (m_mysql.NextRow())
                    // {
                    //     m_mysql.Value(0, uiResult);
                    //     cout << uiResult << endl;
                    // }
                    if (CDispatchManager::g_mysql.NextRow())
                    {
                        srand((unsigned)time(NULL));
                        string userId,token;
                        stringstream sTime,sRandom,sDeadLine;

                        CDispatchManager::g_mysql.Value(0, userId);
                        time_t nowTime = time(NULL);
                        
                        int64_t time = (int64_t)nowTime;
                        int64_t deadLine = time + 604800;
                        sTime << time;
                        sRandom << (int64_t)rand();
                        sDeadLine << deadLine;
                        respDto.status = "1";
                        respDto.token = sTime.str() + userId + sRandom.str();
                        // Sha256(token,(uint8_t*)respDto.token.data(),respDto.token.length());
                        // cout<<token<<endl;
                        respDto.token = token;
                        respDto.deadLine = sDeadLine.str();
                    }
                    else
                    {
                        respDto.status = "0";
                    }
                }

                m_http.Destroy();
                CDispatchManager::DispatchHttpResponse(respDto.Serialize().c_str(), client);
            }
            else
            {
                CDispatchManager::DispatchHttpResponse("", client, false);
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