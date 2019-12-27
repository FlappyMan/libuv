
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
};

#endif
