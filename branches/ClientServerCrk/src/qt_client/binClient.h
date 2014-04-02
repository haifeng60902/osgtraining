#ifndef _BIN_CLIENT_H_
#define _BIN_CLIENT_H_

#include <vector>
#include <string>
#include <map>

typedef std::vector<std::string> tVecStr;

struct binCoin
{
	std::string sCoin;
	std::string sMiner;
	std::string sIcon;
	tVecStr vPools;
};

typedef std::vector<binCoin> tVecCoin;

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
		iPort(4028)
	{};
	bool bShowSysTray;
	std::string sUser;
	std::string sPass;
	std::string sHost;
	int iPort;
	tMapMiner mMiners;
	tVecCoin vCoins;
};

#endif	//_BIN_CLIENT_H_