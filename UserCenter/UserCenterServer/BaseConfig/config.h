
#ifndef _CONFIG_HEADER_
#define _CONFIG_HEADER_

#include "UBaseLib.h"
#include <fstream>


class Config
{
public:
    Config();
    ~Config();
    static bool Load(string &sPath);

public:
    static string g_sListenIP;
    static uint16_t g_uiListenPort;
    static string g_connectKey;

    static string g_sHttpIP;
    static uint16_t g_uiHttpPort;

    static string sHost;
    static uint16_t uiPort;
    static string sUser;
    static string sPwd;
    static string sAccountDB;
    static string sAdminDB;
    static string sAssetsDB;
    static string sBaseDB;
    static string sExassetsDB;
    static string sKycDB;
    static string sOtcDB;
    static string sOtherDB;
    static string sSaDB;
    static string sTradeDB;
};

#endif
