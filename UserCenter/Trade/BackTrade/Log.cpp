#include "Log.h"

const char *LogDir = "Logs/";
const char *LogDirName = "Logs";
const char *LogTail = ".log";
const char *CreateLogCommand = "mkdir Logs";
CLogger_Debug::CLogger_Debug()
{
	m_iFD = -1;
}

CLogger_Debug::~CLogger_Debug()
{
}

/**************************************************
* 类名		: CLogger_Debug
* 函数名	: getMorningTime
* 返回类型	: time_t
* 函数功能	: 获取当前0点0分0秒的时间戳，用于命名当天的日志文件
**************************************************/
time_t CLogger_Debug::getMorningTime()
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	tm->tm_hour = 0;
	tm->tm_min = 0;
	tm->tm_sec = 0;
	return mktime(tm);
}

/**************************************************
* 类名		: CLogger_Debug
* 函数名	: OpenFile
* 返回类型	: bool
* 函数功能	: linux的open函数，权限为读写，创建
**************************************************/
bool CLogger_Debug::OpenFile(string &szFileName)
{
	m_iFD = open((char *)szFileName.c_str(), O_RDWR | O_APPEND | O_CREAT, 0);
	if (m_iFD == -1)
		return false;
	else
		return true;
}

void CLogger_Debug::Logger_Debug(const char *pParamName)
{
	if (false == GetLogFileName())
	{
		return;
	}
	string szParmComb = pParamName;
	szParmComb += '\n';
	write(m_iFD, (char *)szParmComb.c_str(), szParmComb.length() + 1);
	fsync(m_iFD);
}

/**************************************************
* 类名		: CLogger_Debug
* 函数名	: SetLogFileName
* 返回类型	: string
* 函数功能	: 设置日志的文件名称
* 参数描述	: 文件名以当天时间0点0分0秒为名
**************************************************/
void CLogger_Debug::SetLogFileName(string &szDebugFileName)
{
	szDebugFileName = LogDir;
	time_t timeSamp = getMorningTime();
	time_t timep = time(NULL);
	struct tm *pNow = localtime(&timep);
	struct tm *pRecord = localtime(&timeSamp);

	if (pRecord->tm_mday != pNow->tm_mday)
	{
		m_iFD = -1;
	}
	szDebugFileName += std::to_string(timeSamp);

	szDebugFileName += LogTail;
}

/**************************************************
* 类名		: CLogger_Debug
* 函数名	: CreateLogDIR
* 返回类型	: void
* 函数功能	: 在程序运行的目录下创建一个Logs文件夹
* 参数描述	: none
**************************************************/
void CLogger_Debug::CreateLogDIR()
{
	if (0 != access(LogDirName, 0))
		system(CreateLogCommand);
}

/**************************************************
* 类名		: Clogger_Debug
* 函数名	: GetLogFileName
* 返回类型	: bool
* 函数功能	: 根据上层目录名称来创建日志文件
* 如文件目录为 /MyFile/Mytest/ 下的程序目录，则日志文件为
* LOGGERDEBUG_Mytest_1.log 其中.log前数字依次递加
* 参数描述	: none
**************************************************/
bool CLogger_Debug::GetLogFileName()
{
	string szDebugFileName = "";

	CreateLogDIR();
	SetLogFileName(szDebugFileName);

#ifdef DEBUG
	if (-1 == m_iFD)
	{
		assert(true == OpenFile(szDebugFileName));
	}
#else
	if (-1 == m_iFD)
	{
		if (false == OpenFile(szDebugFileName))
		{
			return false;
		}
	}
#endif
	return true;
}