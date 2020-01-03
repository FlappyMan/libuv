#ifndef _LOADCONFIG_H_
#define _LOADCONFIG_H_
#include "BackTrade_Marco.h"
using namespace std;

class CLoadConfig
{
public:
	CLoadConfig(){};
	~CLoadConfig(){};

public:
	string		GetConfigParmName(const char *pParmName);
	
private:
	void		CheckData(string &str);
};

#endif

