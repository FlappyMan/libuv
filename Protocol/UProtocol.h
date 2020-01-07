#ifndef _UPROTOCOL_H_
#define _UPROTOCOL_H_

#include "UBaseLib.h"
#include "UProtocol_Header.h"


using namespace std;
enum
{
	PROTOCOL_LEN_MAX=2*1024*1024,	// 最大包长度2M Byte
};

// return <0: 协议错误，=0:数据包长度不足，>0:第一个包长度
int ProtocolHead(uint16_t &uiType,uint32_t &uiValueLen,char *pBuff,int iLen);

template<class UProtocol>
int ProtoPackSize(UProtocol &up)
{
	string str;
	if(up.SerializeToString(&str)==false)
	{
		return 0;
	}
	return str.length()+sizeof(uint16_t)+sizeof(uint32_t);
};

template<class UProtocol>
int ProtoPack(char *pBuff,uint32_t uiLen, UProtocol &up)
{
	string str;
	if(up.SerializeToString(&str)==false)
	{
		return 0;
	}
	const int iPkgSize=str.length()+sizeof(uint16_t)+sizeof(uint32_t);
	if(uiLen<(uint32_t)iPkgSize)
	{
		return -iPkgSize;
	}
	uint16_t uiType=htons(up.CMD);
	uint32_t uiPkgLen=htonl(str.length());

	char *pos=pBuff;
	memcpy(pos,&uiType,sizeof(uint16_t));
	pos+=sizeof(uint16_t);
	memcpy(pos,&uiPkgLen,sizeof(uint32_t));
	pos+=sizeof(uint32_t);
	memcpy(pos,str.c_str(),str.length());
	return iPkgSize;
};

// pBuff: 包含包头6个字节
template<class UProtocol>
bool ProtoUnpack(UProtocol &up,char *pBuff,uint32_t uiLen)
{
	char *pos=pBuff+sizeof(uint16_t)+sizeof(uint32_t);
	string str(pos,uiLen);
	stringstream ss(str) ;
	if(up.ParseFromString(str))
	{
		uint16_t *pType=(uint16_t*)pBuff;
		up.m_uiType=ntohl(*pType);
		uint32_t *pLen=(uint32_t*)(pBuff+sizeof(uint16_t));
		up.m_uiPkgLength=ntohl(*pLen);
		return true;

	}
	return false;		
};

template<class UProtocol>
int JsonPack(UProtocol *p,char *pBuff,uint32_t uiLen)
{
	Json::Value root;
	p->JsonPack(root);
	return UBJsonPack(pBuff,uiLen,root);
};

template<class UProtocol>
bool JsonUnpack(UProtocol *p,char *pBuff,uint32_t uiLen)
{
	Json::Value root;
	if(UBJsonUnpack(root,pBuff,uiLen)==false)return false;
	return p->JsonUnpack(root);
};

#endif







