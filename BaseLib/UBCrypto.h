
#ifndef _UBCRYPTO_HEADER_
#define _UBCRYPTO_HEADER_

#include "UBHeader.h"
#include "openssl/evp.h"
#include "openssl/bio.h"
#include "openssl/buffer.h"
#include "openssl/sha.h"

bool Base64Encode(string &strEncoded,const char *pData, int iDataLen, bool bNewLine=false);
bool Base64Decode(string &strDecoded,const char *pData, int iDataLen, bool bNewLine=false);


#endif
