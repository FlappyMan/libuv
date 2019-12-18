
#include "global.h"
#include "ThreadClient.h"
#include "ThreadBackTrade.h"



bool InitDaemon()
{
    return true;
}

// load config & init daemon
bool Init(int argc, char *argv[])
{
    if(argc<2)
    {
        cout<<argv[0]<< "config.txt"<<endl;
        return false;
    }

    enum{BUFF_SIZE=512};
    char sBuffer[BUFF_SIZE]={0};
    char *pBuffer=getcwd(sBuffer,BUFF_SIZE);
    if(pBuffer==NULL)return false;

    g_dir_root=pBuffer;
    g_dir_root.append(1,'/');

    string sConfigPath=g_dir_root+argv[1];
    if(g_config.Load(sConfigPath)==false)
    {
        cout<<"Load config file failed"<<endl;
        return false;
    }

    if(InitDaemon()==false)
    {
        cout<<"Init Daemon failed"<<endl;
        return false;
    }

    return true;
}


int main(int argc, char *argv[])
{
    if(Init(argc,argv)==false)
    {
        cout<<"Init failed"<<endl;
        return 0;
    }

    g_cache_write_req.Init(g_config.m_uiWriteCahce2k,g_config.m_uiWriteCahce8k,g_config.m_uiWriteCahce16k);

    uv_thread_t tClient,tBackTrade;
	uv_thread_create(&tBackTrade, ThreadBacktrade, NULL);
	uv_thread_create(&tClient, ThreadClient, NULL);

	uv_thread_join(&tClient);
	uv_thread_join(&tBackTrade);

    g_cache_write_req.Destroy();

    return 0;
}


