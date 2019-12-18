
#include "UBaseLib.h"


int main()
{
	enum{STR_LEN=200};
	char str[STR_LEN];

	UBHttpParser hp;
	hp.Init(HTTP_RESPONSE);

	getcwd(str,STR_LEN);
	string sFilePath=str;
	sFilePath.append("/json-en.html");
	int fd=open(sFilePath.c_str(),O_RDONLY);
	if(fd==-1)
	{
		cout<<"Open file failed:"<<sFilePath<<endl;
		return 0;
	}

	struct stat _stat;
	fstat(fd,&_stat);

	int ret=0;
	int iReaded=0;
	int iReadLen=0;
	while(iReaded<_stat.st_size)
	{
		iReadLen=((_stat.st_size-iReaded) > STR_LEN) ? STR_LEN : (_stat.st_size-iReaded);
		read(fd,str,iReadLen);
		iReaded+=iReadLen;

		ret=hp.Readed(str,iReadLen);
		if(ret<=0)break;
	}
	close(fd);

	for(map<string,string>::iterator it=hp.m_mFiled.begin();it!=hp.m_mFiled.end();it++)
	{
		cout<<it->first<<" :"<<it->second<<endl;
	}

	cout<<hp.m_sBody<<endl;

	return 0;
}