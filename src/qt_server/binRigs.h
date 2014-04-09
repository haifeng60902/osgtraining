#ifndef _BIN_RIGS_H_
#define _BIN_RIGS_H_

#include <vector>
#include <string>

struct binWorker
{
	std::string sWorker;
};
typedef std::vector<binWorker> tVecWorker;
typedef std::vector<std::string> tVecString;

struct binMode
{
	std::string sCoin;
	std::string sMiner;
	std::string sIcon;
	tVecString vPools;
};

typedef std::vector<binMode> tVecMode;

struct  binSetting
{
	binSetting():iColumn(0)
		,iPort(9800)
	{};

	int iColumn;
	int iPort;
	tVecWorker vWorker;
	tVecMode vModes;
};

#endif	//_BIN_RIGS_H_