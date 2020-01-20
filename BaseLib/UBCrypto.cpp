
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
    BIO_read(pPublicKey, buffer, uiPublic); 
    sPublicKey.assign(buffer,uiPublic);
    delete []buffer;

    RSA_free(rsa);
}

void Sha256(string &hash,const uint8_t *pData,uint32_t uiLen)
{	
    uint8_t out[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, pData, uiLen);
    SHA256_Final(out, &sha256);

    hash.assign((char*)out,SHA256_DIGEST_LENGTH);
}
/*
 *  1、Blowfish默认分组大小BF_BLOCK=8Byte;
 *	2、in_size为待加密字符串的实际长度(不包含字符串结束符'\0'),out_size为加密后字符串的实际长度(不包含字符串结束符'\0');
 * 	   BF_BLOCK分组加密大小为8Byte,加密后的out_size为8的整数倍;
 *	3、如果待加密的字符串长度(不包含字符串结束符'\0')不是8的整数倍,补齐整数倍并以'0'填充。如果是8的整数倍,如2倍,
 *	   补齐成3倍长度,补齐的8Byte以'0'填充;
 * 	4、例:in_size = 7Byte,则in补齐到8Byte，out_size = 8Byte;如in_size = 8Byte,则in补齐到16Byte,out_size = 16Byte;
 */
int BlowfishEncrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size)
{
    int in_block_cnt = in_size/BF_BLOCK+1;
    int in_size_need = in_block_cnt*BF_BLOCK;
    int out_size_need = in_size_need;
    if (out_size < in_size_need)
    {
        cout<<"BF_ENCRYPT Arg 3 need a larger size: "<<-in_size_need<<endl;
        return -in_size_need;
    }	
    const unsigned char key[BF_BLOCK*2] = "UkexServerKey";
    int key_len = strlen((const char*)key);

    unsigned char* in_mem_need = new unsigned char[in_size_need];
    memset((void*)in_mem_need,0,in_size_need);
    memcpy((char*)in_mem_need,(const char*)in,in_size);

    BF_KEY bf_key;
    BF_set_key(&bf_key, key_len, key);

    int len = 0;
    while (len < in_size_need)
    {
        BF_ecb_encrypt(in_mem_need+len, out+len, &bf_key, BF_ENCRYPT);
        len += BF_BLOCK;
    }
    delete[] in_mem_need;
    in_mem_need = NULL;
    return out_size_need;
}

int BlowfishDecrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size)
{
    if (out_size < in_size-BF_BLOCK)
    {
        cout<<"BF_ENCRYPT Arg 3 need a larger size: "<<-(in_size-BF_BLOCK)<<endl;
        return -(in_size-BF_BLOCK);
    }	
    const unsigned char key[BF_BLOCK*2] = "UkexServerKey";
    int key_len = strlen((const char*)key);

    BF_KEY bf_key;
    BF_set_key(&bf_key, key_len, key);

    int len = 0;
    while (len < in_size)
    {
        BF_ecb_encrypt(in+len, out+len, &bf_key, BF_DECRYPT);
        len += BF_BLOCK;
    }
    return out_size;
}
/*
 *  1、AES默认分组大小AES_BLOCK_SIZE=16Byte;
 *	2、in_size为待加密字符串的实际长度(不包含字符串结束符'\0'),out_size为加密后字符串的实际长度(不包含字符串结束符'\0');
 * 	   AES_BLOCK_SIZE分组加密大小为16Byte,加密后的out_size为16的整数倍;
 *	3、如果待加密的字符串长度(不包含字符串结束符'\0')不是16的整数倍,补齐整数倍并以'0'填充,如果是16的整数倍,如2倍,
 *	   补齐成3倍长度,补齐的16Byte以'0'填充;
 * 	4、例:in_size = 15Byte,则in补齐到16Byte，out_size = 16Byte;如in_size = 16Byte,则in补齐到32Byte,out_size = 32Byte;
 */
int AesEncrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size)
{
    int in_block_cnt = in_size/AES_BLOCK_SIZE+1;
    int in_size_need = in_block_cnt*AES_BLOCK_SIZE;
    int out_size_need = in_size_need;
    if (out_size < in_size_need)
    {
        cout<<"AesEncrypt Arg 3 need a larger size: "<<-in_size_need<<endl;
        return -in_size_need;
    }	
    unsigned char user_key[AES_BLOCK_SIZE] = "UkexServerKey";

    unsigned char* in_mem_need = new unsigned char[in_size_need];
    memset((void*)in_mem_need,0,in_size_need);
    memcpy((char*)in_mem_need,(const char*)in,in_size);

    AES_KEY aes_key;
    AES_set_encrypt_key((const unsigned char *)user_key, AES_BLOCK_SIZE*8, &aes_key);
    int len = 0;
    while(len < in_size_need)
    {
        AES_encrypt(in_mem_need+len, out+len, &aes_key);    
        len += AES_BLOCK_SIZE;
    }
    delete[] in_mem_need;
    in_mem_need = NULL;
    return out_size_need;
}

int AesDecrypt(unsigned char *out,const unsigned char *in, int out_size, int in_size)
{
    int in_block_cnt = in_size/AES_BLOCK_SIZE;
    int in_size_need = in_block_cnt*AES_BLOCK_SIZE;
    if (out_size < in_size_need-AES_BLOCK_SIZE)
    {
        cout<<"AesDecrypt Arg 3 need a larger size: "<<-(in_size_need-AES_BLOCK_SIZE)<<endl;
        return -(in_size_need-AES_BLOCK_SIZE);
    }	
    unsigned char user_key[AES_BLOCK_SIZE] = "UkexServerKey";

    unsigned char* in_mem_need = new unsigned char[in_size_need];
    memset((void*)in_mem_need,0,in_size_need);
    memcpy((char*)in_mem_need,(const char*)in,in_size);

    AES_KEY aes_key;
    AES_set_decrypt_key((const unsigned char *)user_key, AES_BLOCK_SIZE*8, &aes_key);
    int len = 0;
    while(len < in_size_need) 
    {
        AES_decrypt(in_mem_need+len, out+len, &aes_key);    
        len += AES_BLOCK_SIZE;
    }
    delete[] in_mem_need;
    in_mem_need = NULL;
    return out_size;
}
