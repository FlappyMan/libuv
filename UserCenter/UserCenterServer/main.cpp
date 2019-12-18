#include "UProtocol.h"
#include "config.h"
#include "global.h"
#include "ThreadTCPOper.h"

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
        cout<<"Init failed"<<endl;
        return -1;
    }
    cout<<"User Center run"<<endl;
    uv_thread_t tTcp,tHttp;
    uv_thread_create(&tTcp, CThreadTCPOper::ThreadTCPOper, NULL);
    // uv_thread_create(&tHttp, ThreadHttpOper, NULL);

    uv_thread_join(&tTcp);
    // uv_thread_join(&tHttp);
    return 0;
}
