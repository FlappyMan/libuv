
#include "UBCrypto.h"



bool Base64Encode(string &strEncoded,const char *pData, int iDataLen, bool bNewLine)
{
	BIO *b64 = BIO_new(BIO_f_base64());
	if (!bNewLine) 
	{
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	}
	BIO *bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, pData, iDataLen);
	BIO_flush(b64);
 
	BUF_MEM *bptr;
	BIO_get_mem_ptr(b64, &bptr);
	BIO_set_close(b64, BIO_NOCLOSE);

	strEncoded.assign(bptr->data, bptr->length);
	BIO_free_all(b64);
	return true;
}

// base64 解码
bool Base64Decode(string &strDecoded,const char *pData, int iDataLen, bool bNewLine)
{
	strDecoded.clear();

	char *buffer = new char[iDataLen];	
	BIO *b64 = BIO_new(BIO_f_base64());
	if (!bNewLine) 
	{
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	}
	BIO *bmem = BIO_new_mem_buf(pData, iDataLen);
	bmem = BIO_push(b64, bmem);
	iDataLen=BIO_read(bmem, buffer, iDataLen);
	BIO_free_all(bmem);

	if(iDataLen>0)
	{
		strDecoded.assign(buffer,iDataLen);
		delete []buffer;
		return true;
	}	
	delete []buffer;
	return false;
}

bool RsaKeyGen(string &sPrivateKey,string &sPublicKey)
{
	sPrivateKey.clear();
	sPublicKey.clear();

	RSA *rsa=RSA_new();
	BIGNUM* bne = BN_new();
	int ret=BN_set_word(bne,RSA_F4);
	if(ret==0)return false;
	ret=RSA_generate_key_ex(rsa,RSA_KEY_BITS,bne,NULL);
	if(ret==0)return false;

	BIO *pPrivateKey = BIO_new(BIO_s_mem());
	PEM_write_bio_RSAPrivateKey(pPrivateKey, rsa, NULL, NULL, 0, NULL, NULL);
	size_t uiPrivate = BIO_pending(pPrivateKey); 
	char *buffer=new char[uiPrivate];
	BIO_read(pPrivateKey, buffer, uiPrivate); 
	sPrivateKey.assign(buffer,uiPrivate);
	delete []buffer;

	BIO *pPublicKey = BIO_new(BIO_s_mem());
	PEM_write_bio_RSAPublicKey(pPublicKey, rsa);
	size_t uiPublic = BIO_pending(pPublicKey); 
	buffer=new char[uiPublic];
	BIO_read(pPrivateKey, buffer, uiPublic); 
	sPublicKey.assign(buffer,uiPublic);
	delete []buffer;

	RSA_free(rsa);
}

/*
bool RsaPublicEncrypt(uint8_t *pOut,uint32_t uiOutSize,uint8_t key[RSA_KEY_LENGTH],uint8_t *pData,uint32_t uiDataLen)
{
	RSA *rsa=RSA_new(void);
    if(rsa==NULL)return -2;

	BIO *keybio = BIO_new_mem_buf(key, RSA_KEY_LENGTH);
	if (keybio==NULL)return false;

	RSA *rsa= NULL;
	EM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
	if(rsa==NULL)return false;

	int iBlockSize=RSA_size(rsa);

	RSA_public_encrypt(uiDataLen,pData,encrypted,rsa,RSA_NO_PADDING);

    RSA_size();

    RSA_private_encrypt(BUFFER_LEN,sBuffer,,rsa,RSA_NO_PADDING);
}


bool RsaPrivateDecrypt()
{

}
*/
