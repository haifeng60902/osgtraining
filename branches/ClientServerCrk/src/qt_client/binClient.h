#ifndef _BIN_CLIENT_H_
#define _BIN_CLIENT_H_

#include <vector>
#include <string>

typedef std::vector<std::string> tVecStr;

struct binCoin
{
	std::string sIcon;
	tVecStr vPools;
};

struct binClient
{
	binClient():bShowSysTray(true)
	{};
	bool bShowSysTray;
	std::string sUser;
	std::string sPass;
};

#endif	//_BIN_CLIENT_H_