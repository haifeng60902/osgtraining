#ifndef _BIN_RIGS_H_
#define _BIN_RIGS_H_

#include <vector>
#include <string>

struct binRig
{
	std::string sRig;
};
typedef std::vector<binRig> tVecRig;
typedef std::vector<std::string> tVecString;

struct binMode
{
	std::string sCoin;
	std::string sMiner;
	tVecString vPools;
};

typedef std::vector<binMode> tVecMode;

struct  binSetting
{
	binSetting():iColumn(0)
	{};

	int iColumn;
	tVecRig vRigs;
	tVecMode vModes;
};

#endif	//_BIN_RIGS_H_