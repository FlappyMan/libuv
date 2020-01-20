
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
#include <openssl/blowfish.h>
#include <openssl/aes.h>

bool Base64Encode(string &strEncoded,const char *pData, int iDataLen, bool bNewLine=false);
bool Base64Decode(string &strDecoded,const char *pData, int iDataLen, bool bNewLine=false);

enum{RSA_KEY_BITS=2048,RSA_KEY_BYTES=256};
bool RsaKeyGen(string &sPrivateKey,string &sPublicKey);

/*in 待加密数据; out 加密后数据; in_size 待加密数据长度; out_size 加密后数据长度*/
int BlowfishEncrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size);
/*in 待解密数据; out 解密后数据; in_size 待解密数据长度; out_size 解密后数据长度*/
int BlowfishDecrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size);

/*in 待加密数据; out 加密后数据; in_size 待加密数据长度; out_size 加密后数据长度*/
int AesEncrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size);
/*in 待解密数据; out 解密后数据; in_size 待解密数据长度; out_size 解密后数据长度*/
int AesDecrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size);

void Sha256(string &hash,const uint8_t *pData,uint32_t uiLen);

#endif
