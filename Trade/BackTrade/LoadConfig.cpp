#include "LoadConfig.h"
#include <fstream>
const char * FolderName = "Config";
const char * CreateFolder = "mkdir Config";
const char * ConfigFilePath = "/Config/Config.ini";
const char * ConfigDesc = "---------------------------------\n## please write the Config file with the rules below \n## for example \n## <pram=value/>    \n## <NAME=WYP/>\n## <AGE=24/>\n## please write the Config Info below     \n---------------------------------";

void	CLoadConfig::CheckData(string &str)
{
	if (str.empty())
	{
		return;
	}
	for (uint32_t iLoop = 0; iLoop < str.length(); iLoop++)
	{
		if (str[iLoop] == '/')
		{
			str = str.substr(0 , iLoop);
			return;
		}
	}
}

string	CLoadConfig::GetConfigParmName(const char *pParmName)
{
	if (pParmName == NULL)
	{
		return "";
	}
	ifstream ReadFile;

	string	szRet	= "";
	char temp[256]={0};
	char szBuff[256]={0};
	char szTemp[256]={0};
	char *pPramValue = NULL;
	getcwd(szBuff,256);
	if (0 != access(FolderName , 0))
		system(CreateFolder);
	sprintf(szTemp,"%s%s",szBuff ,ConfigFilePath);

	ReadFile.open(szTemp,ios::in|ios::out);


	if(ReadFile.fail())
	{
		ofstream out(szTemp , ios::out|ios::app|ios::binary);
		out.close();
		string		szText	= ConfigDesc;
		ofstream note(szTemp,ios::out|ios::app|ios::binary);
		note.write( szText.c_str() , szText.length() );
		note.put('\n');
		note.close();
	}
	else
	{
		while( ReadFile.getline(temp , 256 , '>') )
		{
			if (strstr(temp , pParmName) == NULL)
			{
				continue;
			}
			uint32_t	iStrLen	= strlen(strstr(temp , pParmName));
			if (iStrLen != 0)
			{
				uint32_t iParmLen = strlen(pParmName);
				if ( iStrLen == iParmLen )
				{
					return szRet;
				}
				pPramValue	= new char[iStrLen - iParmLen + 1];
				memset(pPramValue , 0 , iStrLen - iParmLen + 1);
				strncpy(pPramValue , strstr(temp , pParmName) + iParmLen  , iStrLen - iParmLen);
				break;
			}
		}
	}
	if (pPramValue != NULL)
	{
		szRet	= pPramValue;
		if (pPramValue)
		{
			delete pPramValue;
		}
		pPramValue	= NULL;
	}
	CheckData(szRet);
	return szRet;
}