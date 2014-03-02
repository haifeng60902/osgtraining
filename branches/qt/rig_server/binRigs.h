#ifndef _BIN_RIGS_H_
#define _BIN_RIGS_H_

#include <vector>
#include <string>

struct binRig
{
	std::string sRig;
};
typedef std::vector<binRig> tVecRig;

struct  binSetting
{
	binSetting():iColumn(0)
	{};

	int iColumn;
	tVecRig vRigs;
};

#endif	//_BIN_RIGS_H_