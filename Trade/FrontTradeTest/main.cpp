#include "UProtocol.h"
#include "ThreadClient.h"
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
    if(Init(argc,argv)==false)
    {
        cout<<"Init failed"<<endl;
        return -1;
    }
    uv_thread_t client;
    uv_thread_create(&client, ThreadClient, NULL);

    uv_thread_join(&client);
    return 0;
}
