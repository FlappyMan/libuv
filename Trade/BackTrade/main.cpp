#include "UProtocol.h"
#include "./BaseConfig/config.h"
#include "global.h"
#include "ThreadDB.h"
#include "ThreadOrder.h"
#include "ThreadUserCenter.h"
bool Init(int argc, char *argv[])
{
    if(argc<2)
    {
        return false;
    }

    enum{BUFF_SIZE=512};
    char sBuffer[BUFF_SIZE]={0};
    char *pBuffer=getcwd(sBuffer,BUFF_SIZE);
    if(pBuffer==NULL)return false;

    g_dir_root=pBuffer;

    string sConfigPath=g_dir_root+"/"+argv[1];
    if(Config::Load(sConfigPath)==false)
    {
        cout<<"Load config file failed"<<endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if(Init(argc,argv)==false)
    {
        cout<<"[BackTrade Init Failed]"<<endl;
        return -1;
    }
    cout<<"[BackTrade running]"<<endl;
    uv_thread_t tOrderThread,tUCThread,tDBThread,tMatchThread,tControllerThread;
    uv_thread_create(&tOrderThread, CThreadOrder::ThreadOrder, NULL);
    uv_thread_create(&tUCThread, CThreadUserCenter::ThreadUserCenter, NULL);
    // uv_thread_create(&tOrderThread, CThreadDB::ThreadDB, NULL);

    uv_thread_join(&tOrderThread);
    uv_thread_join(&tUCThread);
    // uv_thread_join(&tDBThread);
    // uv_thread_join(&tMatchThread);
    // uv_thread_join(&tControllerThread);
    return 0;
}
