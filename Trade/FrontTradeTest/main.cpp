#include "UProtocol.h"
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
void BlowfishTest()
{
    unsigned char *source = new unsigned char[BF_BLOCK*2];
    unsigned char *buf = new unsigned char[BF_BLOCK*3+4];
    unsigned char *recBuf = new unsigned char[BF_BLOCK*2];
    memset((void*)source, 'p', BF_BLOCK*2);
    memset((void*)buf,0,BF_BLOCK*3+4);
    memset((void*)recBuf,0,BF_BLOCK*3);
    BlowfishEncrypt(buf,source,BF_BLOCK*3+4,BF_BLOCK*2);
    BlowfishDecrypt(recBuf,(const unsigned char*)buf,BF_BLOCK*3,BF_BLOCK*3);
    cout<<"buf = ";
    for (size_t i = 0; i < BF_BLOCK*3+4; i++)
    {
        printf("%.2x",buf[i]);
    }
    cout<<endl;
    cout<<"recBuf = "<<recBuf<<endl;
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
    //BlowfishTest();
    uv_thread_t tClient,tBackTrade;
    uv_thread_create(&tBackTrade, ThreadBacktrade, NULL);
    uv_thread_create(&tClient, ThreadClient, NULL);

    uv_thread_join(&tClient);
    uv_thread_join(&tBackTrade);
    return 0;
}
