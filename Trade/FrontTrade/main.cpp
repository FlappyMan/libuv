#include "UProtocol.h"
#include "BlockQueue.h"
#include "ThreadClient.h"
#include "ThreadBackTrade.h"
#include "config.h"
#include "global.h"

void TestLibuv()
{
    uv_loop_t *loop = new uv_loop_t;
    uv_loop_init(loop);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    delete loop;
}

void TestUptrade(UProtocolBase* up2)
{
    UPUptrade up;
    up.set_token("123");
    up.set_paypassword("456");
    up.set_marketid(1);
    up.set_price(2);
    up.set_num(3);
    up.set_type(4);
    up.set_main_coin(5);

    const int BUFFSIZE=1024;
    char buffer[BUFFSIZE];
    int iLen=JsonPack<UPUptrade>(&up,buffer,BUFFSIZE);
    buffer[iLen]='\0';
    //cout<<buffer<<endl;

    JsonUnpack<UProtocolBase>((UProtocolBase *)up2,buffer,iLen);
}

bool Init(int argc, char *argv[])
{
    if(argc<2)
    {
        // cout<<argv[0]<< "config.json"<<endl;
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
    // if(-1 == daemon(1,0))
    // {
    //     return -1;
    // }
    if(Init(argc,argv)==false)
    {
        cout<<"Init failed"<<endl;
        return -1;
    }
    // BlockQueue<UProtocolBase*> proto;
    // UProtocolBase *base = new UPUptrade;
    // TestUptrade(base);
    // proto.put(base);
    // UProtocolBase *pop= proto.get();
    // const int BUFFSIZE=1024;
    // char buffer[BUFFSIZE];
    // int iLen=JsonPack<UProtocolBase>(pop,buffer,BUFFSIZE);
    // buffer[iLen]='\0';
    // cout<<"buff:"<<buffer<<endl;
    // UProtocolBase *upp = new UPUptrade;
    // int itmp=JsonUnpack<UProtocolBase>(upp,buffer,BUFFSIZE);
    // if (UPUptrade::CMD)
    // {
    //     /* code */
    // }
    // cout<<dynamic_cast<UPUptrade*>(upp)->token()<<endl;
    // cout<<dynamic_cast<UPUptrade*>(upp)->paypassword()<<endl;
    // cout<<dynamic_cast<UPUptrade*>(upp)->CMD<<endl;

    // cout<<"test : "<<UPUptrade::CMD_WEBAPI<<endl;
    // cout<<"test : "<<UPUptrade::CMD_ROBOTAPI<<endl;

    // char szGmtTime[40] = {0};
    // int timeRet = GetGMTime(szGmtTime);
    // cout<<"time : "<< szGmtTime<<endl;

    uv_thread_t tClient,tBackTrade;
    uv_thread_create(&tBackTrade, ThreadBacktrade, NULL);
    uv_thread_create(&tClient, ThreadClient, NULL);

    uv_thread_join(&tClient);
    uv_thread_join(&tBackTrade);
    return 0;
}
