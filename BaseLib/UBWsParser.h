
#ifndef _UBWSPARSER_HEADER_
#define _UBWSPARSER_HEADER_

#include "UBHttpParser.h"



enum UBWsParserFrameType 
{
	ERROR_FRAME=0xFF00,
	INCOMPLETE_FRAME=0xFE00,

	OPENING_FRAME=0x3300,
	CLOSING_FRAME=0x3400,

	INCOMPLETE_TEXT_FRAME=0x01,
	INCOMPLETE_BINARY_FRAME=0x02,

	TEXT_FRAME=0x81,
	BINARY_FRAME=0x82,

	PING_FRAME=0x19,
	PONG_FRAME=0x1A
};



class UBWsParser : public UBHttpParser
{
public:
    UBWsParser(){};
    ~UBWsParser(){};

	bool WSReplyHeader(string &sOutHeader);		// 生成 WebSocket的返回头
	int64_t WSSetFrame(UBWsParserFrameType ft, uint8_t *pData, uint32_t iDataLen, uint8_t *pBuffer, uint32_t iBufferSize);
	int64_t WSGetFrame(UBWsParserFrameType *pFrameType, uint8_t *pOutBuffer, int iOutBufferSize, uint8_t *pInBuffer, int iInBufferLen);
public:


};

#endif


