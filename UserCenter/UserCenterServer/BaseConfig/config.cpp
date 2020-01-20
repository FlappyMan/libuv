
#include "config.h"

string Config::g_sListenIP = "0.0.0.0";
uint16_t Config::g_uiListenPort = 0;
string Config::g_connectKey = "";

string Config::g_sHttpIP = "0.0.0.0";
uint16_t Config::g_uiHttpPort = 0;

string Config::sHost = "192.168.1.20";
uint16_t Config::uiPort = 3306;
string Config::sUser = "wuyoupeng";
string Config::sPwd = "123456";
string Config::sAccountDB = "account";
string Config::sAdminDB = "admin";
string Config::sAssetsDB = "assets";
string Config::sBaseDB = "base";
string Config::sExassetsDB = "exassets";
string Config::sKycDB = "kyc";
string Config::sOtcDB = "otc";
string Config::sOtherDB = "other";
string Config::sSaDB = "sa";
string Config::sTradeDB = "trade";

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
    if (!ret)
        return false;
    Config::g_sListenIP = root["accept_tcp_ip"].asString();
    Config::g_uiListenPort = root["accept_tcp_port"].asUInt64();
    Config::g_connectKey = root["connect_key"].asString();
    Config::g_uiHttpPort = root["accept_http_port"].asUInt64();
    Config::g_sHttpIP = Config::g_sListenIP;

    Config::sHost = root["host"].asString();
    Config::uiPort = root["port"].asUInt64();
    Config::sUser = root["user"].asString();
    Config::sPwd = root["password"].asString();
    Config::sAccountDB = root["account"].asString();
    Config::sAdminDB = root["admin"].asString();
    Config::sAssetsDB = root["assets"].asString();
    Config::sBaseDB = root["base"].asString();
    Config::sExassetsDB = root["exassets"].asString();
    Config::sKycDB = root["kyc"].asString();
    Config::sOtcDB = root["otc"].asString();
    Config::sOtherDB = root["other"].asString();
    Config::sSaDB = root["sa"].asString();
    Config::sTradeDB = root["trade"].asString();
    return true;
}
