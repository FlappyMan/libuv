#ifndef _BACKTRADE_MARCO_H_
#define _BACKTRADE_MARCO_H_

#include "UProtocol.h"
using namespace std;

#define DEBUG


#define SERVER_IP				"192.168.1.20"
#define PVTP_LEN				4				// 协议包头长度
#define	PRO_SUCCESS				1				
#define PRO_FAILED				0
#define PRO_HOLD				2
#define	SERVER_PORT				8070			// 服务器监听端口
#define	SOCK_MAX_LISTEN			100				// 服务器socket最大监听数
#define	EPOLL_SIZE				10				// epoll大小
#define USERNAME				20				// 用户名长度
#define MESSAGE_HEADER			12				// 协议包头长度
#define MESSAGE_BODY_MAX		75				// 协议包体的最大数据包大小
#define SEND_SOUND_DATA_LEN		160				// 声音数据包长；（320个char或160个short）
#define LOGGER_DEBUG			m_stLog.Logger_Debug
#define	LOGGER_SETTAG			m_stLog.SetLogUniqSign
#define	LOGGER_SIZE				m_stLog.SetLoggerSize
#define FILE_PATH_LEN			256
#define LENGTH125				125

// 执行sql语句的类型
enum  tagSqlStatus
{
	SELECT_SQL   =1,
	INSERT_SQL   =2,
	DELETE_SQL   =3,
	UPDATE_DQL   =4
};

// 获取SQL语句一行的所有字段
enum tagGetEachFiled
{
	Filed1  = 0,
	Filed2  = 1,
	Filed3  = 2,
	Filed4,
	Filed5,
	Filed6,
	Filed7,
	Filed8,
	Filed9,
	Filed10,
	Filed11,
	Filed12,
	Filed13,
	Filed14,
	Filed15,
	Filed16,
	Filed17
};

#define SDPLOG_ERROR(strFuncName) try\
	{\
		auto my_logger = spdlog::basic_logger_mt(typeid(strFuncName).name(), "logs/BackTrade.txt");\
		stringstream s;\
		s<<__LINE__;\
		my_logger->error(string(__FILE__) + string(":") + string(__func__) + string(":") + s.str());\
		spdlog::drop_all();\
	}\
	catch (const spdlog::spdlog_ex &ex)\
	{\
		std::cout << "Log init failed: " << ex.what() << std::endl;\
	}


#define SDPLOG_INFO(strFuncName,value) try\
	{\
		auto my_logger = spdlog::basic_logger_mt(typeid(strFuncName).name(), "logs/BackTrade.txt");\
		stringstream s;\
		s<<__LINE__;\
		my_logger->info(string(__FILE__) + string(":") + string(__func__) + string(":") + s.str() + string(":")  +value);\
		spdlog::drop_all();\
	}\
	catch (const spdlog::spdlog_ex &ex)\
	{\
		std::cout << "Log init failed: " << ex.what() << std::endl;\
	}

#endif
