#include "UProtocol.h"
#include "BlockQueue.h"
#include "ThreadClient.h"
#include "ThreadBackTrade.h"
#include "config.h"
#include "global.h"

bool Init(int argc, char *argv[])
{
    if(argc<2)
    {
        //cout<<argv[0]<< "config.json"<<endl;
        return false;
    }
    enum{BUFF_SIZE=512};
    char sBuffer[BUFF_SIZE]={0};
    char *pBuffer=getcwd(sBuffer,BUFF_SIZE);
    if(pBuffer==NULL)return false;
    g_dir_root=pBuffer;
    string sConfigPath=g_dir_root+"/"+argv[1];
    if(g_config.Load(sConfigPath)==false)
    {
        cout<<"Load config file failed"<<endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
#if 0 
    if(-1 == daemon(1,0))
    {
        return -1;
    }
#endif
    if(Init(argc,argv)==false)
    {
        cout<<"Init failed"<<endl;
        return -1;
    }

    uv_thread_t tClient,tBackTrade;
    uv_thread_create(&tBackTrade, ThreadBacktrade, NULL);
    uv_thread_create(&tClient, ThreadClient, NULL);

    uv_thread_join(&tClient);
    uv_thread_join(&tBackTrade);
    return 0;
}
