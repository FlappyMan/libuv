

#include "UBMysql.h"


UBMysql::UBMysql(uint32_t uiSqlSize) : m_pMysql(NULL),m_pMysqlResult(NULL),m_iError(0),
	m_pSql(NULL),m_bFreeBuffer(true),m_iSqlSize(uiSqlSize),m_iSqlLength(0),
	m_row(NULL),m_uiColumnCnt(0)
{
	m_pSql=new char[uiSqlSize];
}

UBMysql::UBMysql(char *pSqlBuff,uint32_t uiSqlSize) : m_pMysql(NULL),m_pMysqlResult(NULL),m_iError(0),
	m_pSql(pSqlBuff),m_bFreeBuffer(false),m_iSqlSize(uiSqlSize),m_iSqlLength(0),
	m_row(NULL),m_uiColumnCnt(0)
{
}


UBMysql::~UBMysql()
{
	if(m_pMysql)
	{
		mysql_close(m_pMysql);
	}
	
	if(m_pSql && m_bFreeBuffer)
	{
		delete []m_pSql;
	}
}


void UBMysql::Disconnect()
{
	m_sError.clear();
	m_iError=0;

	m_iSqlLength=0;
	
	m_row=NULL;
	m_uiColumnCnt=0;

	if(m_pMysqlResult!=NULL)
	{
		mysql_free_result(m_pMysqlResult);
		m_pMysqlResult=NULL;
	}

	if(m_pMysql)
	{
		mysql_close(m_pMysql);
		m_pMysql=NULL;
	}
}

bool UBMysql::Connect(string &host,int port,string &user,string &pwd,string &db)
{
	Disconnect();
	
	if(m_pMysql==NULL)
	{
		m_pMysql=mysql_init(NULL);
	}
		
	MYSQL *pRet=mysql_real_connect(m_pMysql,host.c_str(),user.c_str(),pwd.c_str(),db.c_str(),port,NULL,0);
	if(pRet==NULL)
	{
		m_iError=mysql_errno(m_pMysql);
		m_sError=mysql_error(m_pMysql);
		return false;
	}

	mysql_set_character_set(m_pMysql,"utf8");

	return true;
}


bool UBMysql::Connect(string &unixsocket,string &user,string &pwd,string &db)
{
	Disconnect();

	if(m_pMysql==NULL)
	{
		m_pMysql=mysql_init(NULL);
	}
		
	MYSQL *pRet=mysql_real_connect(m_pMysql,NULL,user.c_str(),pwd.c_str(),db.c_str(),0,unixsocket.c_str(),0);
	if(pRet==NULL)
	{
		m_iError=mysql_errno(m_pMysql);
		m_sError=mysql_error(m_pMysql);
		return false;
	}

	mysql_set_character_set(m_pMysql,"utf8");

	return true;
}


void UBMysql::_ClearSelect()
{
	if(m_pMysqlResult)
	{
		mysql_free_result(m_pMysqlResult);
		m_pMysqlResult=NULL;
	}
	m_row=NULL;
	m_uiColumnCnt=0;
}

bool UBMysql::Sql(const char *pSql,int iSqlLen,bool bCleanBuffer)
{
	if(m_pMysql==NULL)return false;

	if(bCleanBuffer)m_iSqlLength=0;
	if(iSqlLen*2+1 >= (m_iSqlSize-m_iSqlLength))return false;
	
	int iAppened=mysql_real_escape_string(m_pMysql,m_pSql+m_iSqlLength,pSql,iSqlLen);
	m_iSqlLength+=iAppened;
	return true;
}


int UBMysql::Exec(const char *sql,int len)
{
	if(m_pMysql==NULL)return -1;

	_ClearSelect();
	
	// int mysql_real_query(MYSQL *mysql, const char *stmt_str, unsigned long length)
	if(0==mysql_real_query(m_pMysql,sql,len))
	{
		return mysql_affected_rows(m_pMysql);
	}

	m_iError=mysql_errno(m_pMysql);
	m_sError=mysql_error(m_pMysql);
	return -1;
}



bool UBMysql::Select(const char *sql,int len)
{
	if(m_pMysql==NULL)return false;

	_ClearSelect();

	// int mysql_real_query(MYSQL *mysql, const char *stmt_str, unsigned long length)
	if(0!=mysql_real_query(m_pMysql,sql,len))
	{
		m_iError=mysql_errno(m_pMysql);
		m_sError=mysql_error(m_pMysql);
		return false;		
	}
	

	m_pMysqlResult=mysql_use_result(m_pMysql);
	if(m_pMysqlResult==NULL)return false;

	m_uiColumnCnt= mysql_num_fields(m_pMysqlResult);
	return true;
}


bool UBMysql::NextRow()
{
	if(m_pMysqlResult==NULL)return false;

	m_row=mysql_fetch_row(m_pMysqlResult);
	return m_row!=NULL;
}


void UBMysql::Value(uint32_t iIdx,int16_t &iValue,int16_t iDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt || m_row[iIdx]==NULL)
	{
		iValue=iDefault;
		return;
	}

	iValue=atoi(m_row[iIdx]);
}

void UBMysql::Value(uint32_t iIdx,uint16_t &iValue,uint16_t iDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt || m_row[iIdx]==NULL)
	{
		iValue=iDefault;
		return;
	}

	iValue=strtoul(m_row[iIdx],NULL,10);
}


void UBMysql::Value(uint32_t iIdx,int32_t &iValue,int32_t iDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt || m_row[iIdx]==NULL)
	{
		iValue=iDefault;
		return;
	}

	iValue=atoi(m_row[iIdx]);
}

void UBMysql::Value(uint32_t iIdx,uint32_t &uiValue,uint32_t uiDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt || m_row[iIdx]==NULL)
	{
		uiValue=uiDefault;
		return;
	}

	uiValue=strtoul(m_row[iIdx],NULL,10);
}

void UBMysql::Value(uint32_t iIdx,int64_t &iValue,int64_t iDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt)
	{
		iValue=iDefault;
		return;
	}

	iValue=strtol(m_row[iIdx],NULL,10);
}


void UBMysql::Value(uint32_t iIdx,uint64_t &uiValue,uint64_t uiDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt)
	{
		uiValue=uiDefault;
		return;
	}

	uiValue=strtoul(m_row[iIdx],NULL,10);
}


void UBMysql::Value(uint32_t iIdx,float &fValue,float fDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt)
	{
		fValue=fDefault;
		return;
	}

	fValue=strtof(m_row[iIdx],NULL);
}


void UBMysql::Value(uint32_t iIdx,double &dValue,double dDefault)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt)
	{
		dValue=dDefault;
		return;
	}

	dValue=strtod(m_row[iIdx],NULL);
}

void UBMysql::Value(uint32_t iIdx,string &sValue)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt)
	{
		sValue.clear();
		return;
	}

	unsigned long * len=mysql_fetch_lengths(m_pMysqlResult);
	if(len==NULL)
	{
		sValue.clear();
		return;
	}
	
	sValue.assign(m_row[iIdx],len[iIdx]);
}

uint32_t UBMysql::Value(uint32_t iIdx,uint8_t *pBuff,uint32_t iBuffSize)
{
	if(m_row==NULL || iIdx>=m_uiColumnCnt)return 0;

	unsigned long *len=mysql_fetch_lengths(m_pMysqlResult);
	if(len==NULL)return 0;

	uint32_t uiLen=len[iIdx]>=iBuffSize ? iBuffSize : len[iIdx];
	memcpy(pBuff,m_row[iIdx],len[iIdx]);
	return len[iIdx];
}





void UBMysql_Test()
{
	UBMysql mysql(2048);	
//	UBMysql mysql(pSqlBuffer,iSqlBufferLen);

	string sUnixSock,sUser,sPwd,sDB;
	if(mysql.Connect(sUnixSock,sUser,sPwd,sDB))
	{
		int iLastError=mysql.Error();

		string sLastError;
		mysql.Error(sLastError);
		return; 
	}

	// 测试直接传入sql语句 （insert 和 update）
	char sql[]="insert into tableA(columnA) values(1);";
	int iModifiedRows=mysql.Exec(sql,strlen(sql));

	// 测试在内部生成sql语句 （insert 和 update）
	mysql.Sql("insert into tableA(columnB) values(",true);
	mysql.Sql("\r\r)");
	iModifiedRows=mysql.Exec();

	// 测试select 方式 
	string sSqls="insert into tableA(columnA) values(1);";
	bool bOK=mysql.Select(sSqls);
	if(bOK)
	{
		uint32_t uiIndex=0;
		
		uint32_t uiValue=0;
		string sValue;
		while(mysql.NextRow())
		{
			uiIndex=0;
			mysql.Value(uiIndex++,uiValue);
			mysql.Value(uiIndex++,sValue);
		}
	}
	
}



