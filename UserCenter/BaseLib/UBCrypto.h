
#ifndef _UBCRYPTO_HEADER_
#define _UBCRYPTO_HEADER_

#include "UBHeader.h"
#include "openssl/evp.h"
#include "openssl/bio.h"
#include "openssl/buffer.h"
#include "openssl/sha.h"
#include "openssl/rsa.h"
#include <openssl/pem.h>
#include <openssl/bn.h>

bool Base64Encode(string &strEncoded,const char *pData, int iDataLen, bool bNewLine=false);
bool Base64Decode(string &strDecoded,const char *pData, int iDataLen, bool bNewLine=false);

enum{RSA_KEY_BITS=2048,RSA_KEY_BYTES=256};
bool RsaKeyGen(string &sPrivateKey,string &sPublicKey);

void Sha256(string &hash,const uint8_t *pData,uint32_t uiLen);

#endif
