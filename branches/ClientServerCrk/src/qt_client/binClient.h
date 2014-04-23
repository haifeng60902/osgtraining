#ifndef _BIN_CLIENT_H_
#define _BIN_CLIENT_H_

#include <vector>
#include <string>
#include <map>

typedef std::vector<std::string> tVecStr;

struct binLuaCoin
{
	std::string sCoin;
	std::string sMiner;
	std::string sIcon;
	tVecStr vPools;
};

typedef std::vector<binLuaCoin> tVecLuaCoin;

struct binParam
{
	std::string sPath;
	std::string sParam;
};

//key - miner(cgminer,exeminer), value - settings
typedef std::map<std::string, binParam> tMapMiner;

struct binClient
{
	binClient():bShowSysTray(true),
		iPortMiner(4028),iPortServer(9800),
		iWait(1)
	{};
	bool bShowSysTray;
	std::string sUser;
	std::string sPass;
	std::string sHostMiner;
	int iPortMiner;
	std::string sHostServer;
	int iPortServer;
	std::string sLogPath;
	tMapMiner mMiners;
	tVecLuaCoin vCoins;
	int iWait;
};

#endif	//_BIN_CLIENT_H_