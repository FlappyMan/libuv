
#include "config.h"

Config::Config() : m_uiListenPort_BackTrade(6000),m_uiListenPort_Client(443),
    m_uiWriteCahce2k(1000),m_uiWriteCahce8k(1000),m_uiWriteCahce16k(1000),
    m_uiReadCahce2k(1000),m_uiReadCahce8k(1000),m_uiReadCahce16k(1000)
{

}


Config::~Config()
{

}

bool Config::Load(string &sPath)
{
    struct stat stFile;
    if(stat(sPath.c_str(),&stFile)!=0)
    {
        return false;
    }

    ifstream ifile(sPath.c_str());
    if(ifile.is_open()==false)return false;

    char *pBuffer=new char[stFile.st_size];
    ifile.read(pBuffer,stFile.st_size);

    Json::Value root;
    if(UBJsonUnpack(root,pBuffer,stFile.st_size)==false)
    {
        delete []pBuffer;
        return false;
    }
    delete []pBuffer;

    Json::Value &bt=root["BackTrade"];
    m_sListenIP_BackTrade=bt["ip"].asString();
    m_uiListenPort_BackTrade=bt["port"].asUInt();

    Json::Value &client=root["Client"];
    m_sListenIP_Client=client["ip"].asString();
    m_uiListenPort_Client=client["port"].asUInt();

    Json::Value &wc=root["WriteCache"];
    m_uiWriteCahce2k=wc["2k"].asUInt();
    m_uiWriteCahce8k=wc["8k"].asUInt();
    m_uiWriteCahce16k=wc["16k"].asUInt();

    Json::Value &rc=root["ReadCache"];
    m_uiReadCahce2k=rc["2k"].asUInt();
    m_uiReadCahce8k=rc["8k"].asUInt();
    m_uiReadCahce16k=rc["16k"].asUInt();
    return true;
}

