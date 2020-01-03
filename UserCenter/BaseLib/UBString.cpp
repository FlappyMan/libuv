
#include "UBString.h"

void UBStringSplit(vector< std::string > &vRet,const string& str, char d)
{
	string delim(d,1);
	UBStringSplit(vRet,str,delim);
};

void UBStringSplit(vector< std::string > &vRet,const string& str, string& delim)
{
    vRet.clear();

	size_t last = 0;
	size_t index=str.find_first_of(delim,last);
    while (index!=string::npos)
	{
		vRet.push_back(str.substr(last,index-last));
		last=index+1;
		index=str.find_first_of(delim,last);
	}
	if (index>last)
	{
		vRet.push_back(str.substr(last,index-last));
	}
};


void UBStringToUpper(string &s)
{
	for (std::string::size_type i=0; i<s.length(); ++i)
	{
		s[i]=std::toupper(s[i]);
	}
}

void UBStringToLower(string &s)
{
	for (std::string::size_type i=0; i<s.length(); ++i)
	{
		s[i]=std::tolower(s[i]);
	}
}

