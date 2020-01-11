#include "LoginDto.h"
#include "LoginRespDto.h"
#include "DispatchManager.h"
CLoginDto::CLoginDto()
{
    SetProperty(property(usercount));
    SetProperty(property(password));
}
CJsonObjectBase *CLoginDto::requestOperation()
{
#ifdef PRINT_LOG
    cout << "[CLoginDto][requestOperation]" << endl;
#endif
    string sql = "select id from user where user_account = \"" + usercount + "\" and password = \"" + password + "\"";
    bool bHasValue = CDispatchManager::g_mysql.Select(sql);

    CLoginRespDto* respDto = new CLoginRespDto;
    respDto->m_client = m_client;
    if (bHasValue == false)
    {
        respDto->status = "0";
    }
    else
    {
        if (CDispatchManager::g_mysql.NextRow())
        {
            srand((unsigned)time(NULL));
            string userId, token;
            stringstream sTime, sRandom, sDeadLine;

            CDispatchManager::g_mysql.Value(0, userId);
            time_t nowTime = time(NULL);

            int64_t time = (int64_t)nowTime;
            int64_t deadLine = time + 604800;
            sTime << time;
            sRandom << (int64_t)rand();
            sDeadLine << deadLine;
            respDto->status = "1";
            respDto->token = sTime.str() + userId + sRandom.str();
            respDto->token = token;
            respDto->deadLine = sDeadLine.str();
        }
        else
        {
            respDto->status = "0";
        }
    }
    return (CJsonObjectBase *)respDto;
}