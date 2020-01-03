#include "UProtocol.h"

// return <0: 协议错误，=0:数据包长度不足，>0:第一个包长度
int ProtocolHead(uint16_t &uiType,uint32_t &uiValueLen,char *pBuff,int uiLen)
{
    if(uiLen<6)
    {
        return 0;
    }
    memcpy(&uiType,pBuff,sizeof(uint16_t));
    uiType=ntohs(uiType);

    memcpy(&uiValueLen,pBuff+sizeof(uint16_t),sizeof(uint32_t));
    uiValueLen=ntohl(uiValueLen);

    if(uiValueLen>PROTOCOL_LEN_MAX)
    {
        return -1;
    }
    return uiLen;
}


