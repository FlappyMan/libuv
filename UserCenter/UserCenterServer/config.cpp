
#include "config.h"

string Config::g_sListenIP = "0.0.0.0";
uint16_t Config::g_uiListenPort = 0;
string Config::g_connectKey = "";

string Config::g_sHttpIP = "0.0.0.0";
uint16_t Config::g_uiHttpPort = 0;

Config::Config()
{

}


Config::~Config()
{

}

bool Config::Load(string &sPath)
{
    Json::Value root;
    fstream fs(sPath);
    if (!fs)
        return false;
    stringstream ss;
    ss << fs.rdbuf();
    string str(ss.str());
    bool ret = UBJsonUnpack(root, str);
    if(!ret)
        return false;
    Config::g_sListenIP = root["accept_tcp_ip"].asString();
    Config::g_uiListenPort = root["accept_tcp_port"].asUInt64();
    Config::g_connectKey = root["connect_key"].asString();
    Config::g_uiHttpPort = root["accept_http_port"].asUInt64();
    Config::g_sHttpIP = Config::g_sListenIP; 
    return true;
}

