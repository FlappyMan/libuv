
#include "UBWsParser.h"



int64_t UBWsParser::WSSetFrame(UBWsParserFrameType ft, uint8_t *pData, uint32_t iDataLen, uint8_t *pBuffer, uint32_t iBufferSize)
{
	if(iBufferSize<iDataLen+3)return -(iDataLen+3);

	int64_t pos = 0;
	int64_t iSize = iDataLen;
	pBuffer[pos++] = (uint8_t)ft;

	if (iSize <= 125)
	{
		pBuffer[pos++] = iSize;
	}
	else if (iSize <= 65535)
	{
		pBuffer[pos++] = 126;
		pBuffer[pos++] = (iSize >> 8) & 0xFF;
		pBuffer[pos++] = iSize & 0xFF;
	}
	else
	{
		pBuffer[pos++] = 127;
		for (int i = 3; i >= 0; i--)pBuffer[pos++] = 0;
		for (int i = 3; i >= 0; i--)
		{
			pBuffer[pos++] = ((iSize >> 8 * i) & 0xFF);
		}
	}
	memcpy((void *)(pBuffer + pos), pData, iSize);
	return (iSize + pos);
}

// return <0: 协议错误，0: 收包缓冲长度不足, >0:正常收包，并返回数据长度
int64_t UBWsParser::WSGetFrame(UBWsParserFrameType *pFrameType, uint8_t *pOutBuffer, int iOutBufferSize, uint8_t *pInBuffer, int iInBufferLen)
{
	if (iInBufferLen < 3)return 0;

	uint8_t msg_opcode = pInBuffer[0] & 0x0F;
	uint8_t msg_fin = (pInBuffer[0] >> 7) & 0x01;
	uint8_t msg_masked = (pInBuffer[1] >> 7) & 0x01;

	*pFrameType=ERROR_FRAME;
	if (msg_opcode == 0x0){*pFrameType = (msg_fin) ? TEXT_FRAME : INCOMPLETE_TEXT_FRAME;}
	if (msg_opcode == 0x1){*pFrameType = (msg_fin) ? TEXT_FRAME : INCOMPLETE_TEXT_FRAME;}
	if (msg_opcode == 0x2){*pFrameType = (msg_fin) ? BINARY_FRAME : INCOMPLETE_BINARY_FRAME;}
	if (msg_opcode == 0x9){*pFrameType = PING_FRAME;}
	if (msg_opcode == 0xA){*pFrameType = PONG_FRAME;}
	if(*pFrameType == ERROR_FRAME)return -1;


	int pos = 2;
	int64_t iPayloadLen = 0;
	int iLenField = pInBuffer[1] & (~0x80);
	if (iLenField <= 125)
	{
		iPayloadLen = iLenField;
	}
	else if (iLenField == 126)
	{
		iPayloadLen = ((pInBuffer[2] << 8) | (pInBuffer[3]));
		pos += 2;
	}
	else if (iLenField == 127)
	{
		iPayloadLen = (  (uint64_t)(pInBuffer[2]) << 56) |
						  ((uint64_t)(pInBuffer[3]) << 48) |
						  ((uint64_t)(pInBuffer[4]) << 40) |
						  ((uint64_t)(pInBuffer[5]) << 32) |
						  ((uint64_t)(pInBuffer[6]) << 24) |
						  ((uint64_t)(pInBuffer[7]) << 16) |
						  ((uint64_t)(pInBuffer[8]) << 8) |
						  ((uint64_t)(pInBuffer[9]) 
						  );
		pos += 8;
	}
	if (iInBufferLen < iPayloadLen + pos)return 0;

	if (msg_masked)
	{
		unsigned int mask = 0;
		mask = *((unsigned int *)(pInBuffer + pos));
		pos += 4;

		uint8_t *c = pInBuffer + pos;
		for (int i = 0; i < iPayloadLen; i++)
		{
			c[i] = c[i] ^ ((uint8_t *)(&mask))[i % 4];
		}
	}

	if (iPayloadLen > iOutBufferSize)
	{
		return -iPayloadLen;
	}

	memcpy((void *)pOutBuffer, (void *)(pInBuffer + pos), iPayloadLen);
	return iPayloadLen;
}
