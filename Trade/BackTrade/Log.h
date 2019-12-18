#ifndef _LOGGER_DEBUG_H_
#define _LOGGER_DEBUG_H_
/********************************************************
* 类名      : CLoger_Debug
* 基类名    : NONE
* author    : W.Y.P
* 创建日期  : 2012/05/22
* 返回值    : NONE
* 描述      : 用于打印日志文件采用C++文件操作流实现
*			: 日志默认大小每个100MB,可通过函数SetLoggerSize进行设置
*			: 日志打满100个则会进行清空所有日志文件的处理
*********************************************************/
#include "BackTrade_Marco.h"

using namespace std;
class CLogger_Debug
{

public:
	CLogger_Debug();
	~CLogger_Debug();


public:
	void		Logger_Debug(const char *pParamName);

private:
	bool		OpenFile(string &szFileName);		// 成功打开文件，返回打开的文件指针
	void		CreateLogDIR();
	bool		GetLogFileName();
	void		SetLogFileName(string &szDebugFileName);
	time_t 		getMorningTime();

private:
	int			m_iFD;	// 写入文件句柄
};
#endif

