#include <stdlib.h>
#include <stdio.h>

#include "UProtocol.h"



enum
{
	SQL_BUFF_SIZE = 4096
};
void TestMysql()
{
	string sError;
	string sHost = "127.0.0.1";
	uint16_t uiPort = 3306;
	string sUser = "grant";
	string sPwd = "123456";
	string sDB = "grant_test";

	// 创建mysql 对象，并连接数据库
	UBMysql mysql(SQL_BUFF_SIZE);
	bool bConnected = mysql.Connect(sHost, uiPort, sUser, sPwd, sDB);
	if (bConnected == false)
	{
		mysql.Error(sError);
		cout << "connect to database failed:" << mysql.Error() << ":" << sError << endl;
		return;
	}
	cout << "connect to database:" << sHost << ":" << uiPort << endl;

	// 执行一条sql语句，删除已经存在的表
	string sql = "DROP TABLE A;";
	int iRet = mysql.Exec(sql);
	cout << sql << endl;
	if (iRet < 0)
	{
		mysql.Error(sError);
		cout << "exec sql failed:" << mysql.Error() << ":" << sError << endl;
	}

	// 创建一张新表A
	sql = "create table A(id int not null default 0);";
	cout << sql << endl;
	iRet = mysql.Exec(sql);
	if (iRet < 0)
	{
		mysql.Error(sError);
		cout << "exec sql failed:" << mysql.Error() << ":" << sError << endl;
	}

	// 向表A中插入100条数据
	int iSqlLen = 0;
	char sSql[256];
	for (int i = 0; i < 100; i++)
	{
		iSqlLen = snprintf(sSql, 256, "insert into A(id) values(%u)", i);
		cout << sSql << endl;
		mysql.Exec(sSql, iSqlLen);
	}

	// 从表A中查询全部数据，并打印
	sql = "select id from A";
	cout << sql << endl;
	bool bHasValue = mysql.Select(sql);
	if (bHasValue == false)
	{
		cout << sql << " has no record" << endl;
	}

	uint32_t uiResult = 0;
	while (mysql.NextRow())
	{
		mysql.Value(0, uiResult);
		cout << uiResult << endl;
	}

	// 断开连接
	mysql.Disconnect();
}

void TestJson()
{
	string str = "";

	Json::Value root;
	root["key"] = Json::Value("value");
	UBJsonPack(str, root, true);
	cout << "json:" << str << endl;

	root.clear();
	UBJsonUnpack(root, str);

	cout << root["key"] << endl;
}

void TestJson2()
{
	string str = "{}";

	Json::Value root;
	UBJsonPack(str, root, true);

	Json::Value &v = root["key"];
	if (root["key"].isNull())
	{
		cout << "json has no key" << endl;
		return;
	}

	if (root["key"]["key2"].isNull())
	{
		cout << "json has no key.key2" << endl;
		return;
	}

	int x = root["key"]["key2"].asUInt();

	cout << "All Ok:" << x << endl;
	return;
}

void TestUBBuffer()
{
	string a = "aaaaaaaaaa";
	string b = "bbbbbbbbbb";
	string c = "cccccccccc";

	UBBuffer buffer(2048);
	buffer.AppendData(a);

	string str(buffer.Data(), buffer.DataLength());
	cout << "a only:\t" << str << endl;

	buffer.AppendData(b);
	str.assign(buffer.Data(), buffer.DataLength());
	cout << "a & b:\t" << str << endl;

	buffer.RemoveData(a.length());
	str.assign(buffer.Data(), buffer.DataLength());
	cout << "b only:\t" << str << endl;

	buffer.AppendData(c);
	str.assign(buffer.Data(), buffer.DataLength());
	cout << "b & c:\t" << str << endl;

	buffer.RemoveData(b.length());
	str.assign(buffer.Data(), buffer.DataLength());
	cout << "c only:\t" << str << endl;

	buffer.RemoveData(c.length());
	str.assign(buffer.Data(), buffer.DataLength());
	cout << "nothing left:\t" << str << endl;

	UBBuffer buffer2(2048);
	buffer2.AppendData(a);
	buffer2.AppendData(b);
	buffer2.AppendData(c);
	buffer2.Swap(&buffer);
	str.assign(buffer.Data(), buffer.DataLength());
	cout << "after swap(a & b & c):" << str << endl;

	buffer.Clear();
	str.assign(buffer.Data(), buffer.DataLength());
	cout << "after clear():" << str << endl;
}

class A
{
public:
	A(){};
	virtual ~A() { cout << "~A()" << endl; };

public:
	int a1 = 1;
	int a2 = 2;
};

class B
{
public:
	B(){};
	virtual ~B() { cout << "~B()" << endl; };

public:
	int b1 = 3;
	int b2 = 4;
};

class C : public A, public B
{
public:
	C(){};
	~C() { cout << "~C()" << endl; };

public:
	int c1 = 5;
	int c2 = 6;
};

void TestInherit()
{
	{C c;
		A *a = &c;
		cout << a->a1 << endl;
	}
	{
		C *c = new C;
		A *a = c;
		cout << "begin delete a" << endl;
		delete a;
		cout << "end delete a" << endl;
	}
}

// return <0: 输出长度不够(所需长度负值), =0: 未执行，>0:加密后长度
int RSA_Private_Encrypt(uint8_t *pOut,int iOutLen,string &key,uint8_t *pIn,int iInLen)
{
	int iEncodeLen=RSA_KEY_BYTES - (iInLen % RSA_KEY_BYTES) + iInLen;
	if(iOutLen<iEncodeLen)return -iEncodeLen;

	BIO *bio = BIO_new_mem_buf(key.data(), key.length());
	if (bio==NULL)return 0;

	RSA *rsa= NULL;
	rsa=PEM_read_bio_RSAPrivateKey(bio, &rsa,NULL, NULL);
	if(rsa==NULL)
	{
		BIO_free(bio);
		return 0;
	}

	uint8_t from[RSA_KEY_BYTES]={0};
	uint8_t to[RSA_KEY_BYTES]={0};

	int len=0;
	uint8_t *o=pOut;
	for(uint8_t *i=pIn;i<pIn+iInLen;)
	{
		len=(pIn+iInLen-i)>RSA_KEY_BYTES ? RSA_KEY_BYTES : (pIn+iInLen-i);
		if(len==RSA_KEY_BYTES)
		{
			RSA_private_encrypt(len,i,o,rsa,RSA_NO_PADDING);
		}
		else
		{
			memcpy(from,i,len);
			RSA_private_encrypt(len,from,o,rsa,RSA_NO_PADDING);
		}
		i+=len;
		o+=len;
	}

	BIO_free(bio);
	RSA_free(rsa);

	return iEncodeLen;
}


// return <0: 输出长度不够(所需长度负值), =0: 未执行，>0:加密后长度
int RSA_Public_Decrypt(uint8_t *pOut,int iOutLen,string &key,uint8_t *pIn,int iInLen)
{
	if(iInLen%RSA_KEY_BYTES != 0)return 0;
	if(iOutLen<iInLen)return -iInLen;

	BIO *bio = BIO_new_mem_buf(key.data(), key.length());
	if (bio==NULL)return 0;

	RSA *rsa= NULL;
	rsa=PEM_read_bio_RSAPublicKey(bio, &rsa,NULL, NULL);
	if(rsa==NULL)
	{
		BIO_free(bio);
		cout<<"PEM_read_bio_RSAPublicKey failed"<<endl;
		return 0;
	}

	uint8_t from[RSA_KEY_BYTES]={0};
	uint8_t to[RSA_KEY_BYTES]={0};

	int len=0;
	uint8_t *o=pOut;
	for(uint8_t *i=pIn;i<pIn+iInLen;)
	{
		len=(pIn+iInLen-i)>RSA_KEY_BYTES ? RSA_KEY_BYTES : (pIn+iInLen-i);
//		cout<<"encode round:"<<(i-pIn)/RSA_KEY_BYTES<<","<<(i-pIn)<<"+"<<len<<"="<<(i-pIn)+len<<endl;
		if(len==RSA_KEY_BYTES)
		{
			RSA_public_decrypt(len,i,o,rsa,RSA_NO_PADDING);
		}
		else
		{
			memcpy(from,i,len);
			RSA_public_decrypt(len,from,o,rsa,RSA_NO_PADDING);
		}
		i+=len;
		o+=len;
	}

	BIO_free(bio);
	RSA_free(rsa);

	return iInLen;
}



// return <0: 输出长度不够(所需长度负值), =0: 未执行，>0:加密后长度
int RSA_Public_Encrypt(uint8_t *pOut,int iOutLen,string &key,uint8_t *pIn,int iInLen)
{
	int iEncodeLen=RSA_KEY_BYTES - (iInLen % RSA_KEY_BYTES) + iInLen;
	if(iOutLen<iEncodeLen)return -iEncodeLen;
	cout<<"EncodeLen:"<<iEncodeLen<<endl;

	BIO *bio = BIO_new_mem_buf(key.data(), key.length());
	if (bio==NULL)return 0;

	RSA *rsa= NULL;
	rsa=PEM_read_bio_RSAPublicKey(bio, &rsa,NULL, NULL);
	if(rsa==NULL)
	{
		BIO_free(bio);
		cout<<"PEM_read_bio_RSAPublicKey failed"<<endl;
		return 0;
	}

	uint8_t from[RSA_KEY_BYTES]={0};
	uint8_t to[RSA_KEY_BYTES]={0};

	int len=0;
	uint8_t *o=pOut;
	for(uint8_t *i=pIn;i<pIn+iInLen;)
	{
		len=(pIn+iInLen-i)>RSA_KEY_BYTES ? RSA_KEY_BYTES : (pIn+iInLen-i);
//		cout<<"encode round:"<<(i-pIn)/RSA_KEY_BYTES<<","<<(i-pIn)<<"+"<<len<<"="<<(i-pIn)+len<<endl;
		if(len==RSA_KEY_BYTES)
		{
			RSA_public_encrypt(len,i,o,rsa,RSA_NO_PADDING);
		}
		else
		{
			memcpy(from,i,len);
			RSA_public_encrypt(len,from,o,rsa,RSA_NO_PADDING);
		}
		i+=len;
		o+=len;
	}

	BIO_free(bio);
	RSA_free(rsa);

	return iEncodeLen;
}


// return <0: 输出长度不够(所需长度负值), =0: 未执行，>0:加密后长度
int RSA_Private_Decrypt(uint8_t *pOut,int iOutLen,string &key,uint8_t *pIn,int iInLen)
{
	if(iInLen%RSA_KEY_BYTES != 0)return 0;
	if(iOutLen<iInLen)return -iInLen;

	BIO *bio = BIO_new_mem_buf(key.data(), key.length());
	if (bio==NULL)return 0;

	RSA *rsa= NULL;
	rsa=PEM_read_bio_RSAPrivateKey(bio, &rsa,NULL, NULL);
	if(rsa==NULL)
	{
		BIO_free(bio);
		return 0;
	}

	uint8_t from[RSA_KEY_BYTES]={0};
	uint8_t to[RSA_KEY_BYTES]={0};

	int len=0;
	uint8_t *o=pOut;
	for(uint8_t *i=pIn;i<pIn+iInLen;)
	{
		len=(pIn+iInLen-i)>RSA_KEY_BYTES ? RSA_KEY_BYTES : (pIn+iInLen-i);
		if(len==RSA_KEY_BYTES)
		{
			RSA_private_decrypt(len,i,o,rsa,RSA_NO_PADDING);
		}
		else
		{
			memcpy(from,i,len);
			RSA_private_decrypt(len,from,o,rsa,RSA_NO_PADDING);
		}
		i+=len;
		o+=len;
	}

	BIO_free(bio);
	RSA_free(rsa);

	return iInLen;
}

void TestRSA()
{
	string sPrivateKey,sPublicKey;
	RsaKeyGen(sPrivateKey,sPublicKey);
	cout<<"PrivateKey:"<<endl;
	cout<<sPrivateKey<<endl;
	cout<<"PublicKey:"<<endl;
	cout<<sPublicKey<<endl;

	string str;
	enum{DATA_LEN=5945,ENC_LEN=6200,DEC_LEN=6200,};
	uint8_t *data=new uint8_t[DATA_LEN];
	memset(data,'C',DATA_LEN);

	uint8_t *enc=new uint8_t[ENC_LEN];
	uint8_t *dec=new uint8_t[DEC_LEN];

	cout<<"private key crypto"<<endl;
	int ret=RSA_Private_Encrypt(enc,ENC_LEN,sPrivateKey,data,DATA_LEN);
	if(ret>0)
	{
		Base64Encode(str,(char*)enc,ret);
		cout<<str<<endl;
	}

	cout<<"public key decrypto"<<endl;
	ret=RSA_Public_Decrypt(dec,DEC_LEN,sPublicKey,enc,ret);
	cout<<ret<<endl;
	if(ret>0)
	{
		str.assign((char*)dec,ret);
		cout<<str<<endl;
	}

	cout<<"public key crypto"<<endl;
	ret=RSA_Public_Encrypt(enc,ENC_LEN,sPublicKey,data,DATA_LEN);
	cout<<ret<<endl;
	if(ret>0)
	{
		Base64Encode(str,(char*)enc,ret);
		cout<<str<<endl;
	}

	cout<<"private key decrypto"<<endl;
	ret=RSA_Private_Decrypt(dec,DEC_LEN,sPrivateKey,enc,ret);
	cout<<ret<<endl;
	if(ret>0)
	{
		str.assign((char*)dec,ret);
		cout<<str<<endl;
	}


	delete []data;
	delete []enc;
	delete []dec;
}

void TestLogin()
{
	string json="{\"key\":\"Value\"}";
	
	string sPrivateKey,sPublicKey;
	RsaKeyGen(sPrivateKey,sPublicKey);
	cout<<"PrivateKey:"<<endl;
	cout<<sPrivateKey<<endl;
	cout<<"PublicKey:"<<endl;
	cout<<sPublicKey<<endl;


	UPLogin ul;
	int ret=ul.Encode(sPrivateKey,json);
	cout<<"encode ret:"<<ret<<endl;
	{
		string str;
		Base64Encode(str,(char*)ul.key().data(),ul.key().length());
		cout<<str<<endl;
	}

	ret=ul.Decode(json,sPublicKey);
	cout<<"decode ret:"<<ret<<endl;
	cout<<"json:"<<json<<endl;
}



int main()
{
	//	TestMysql();
	//	TestJson();
	//	TestJson2();
	//	TestUBBuffer();
	//  TestInherit();
	// TestRSA();
	//	TestLogin();

	string hash;
	string x="jslkdfjkljskldf ";
	Sha256(hash,(uint8_t*)x.data(),x.length());
	
	string str;
	Base64Encode(str,hash.data(),hash.length());
	cout<<str<<endl;

	return 0;
}
