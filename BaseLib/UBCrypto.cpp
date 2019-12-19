
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

