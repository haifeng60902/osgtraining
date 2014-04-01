#ifndef _BIN_SETTINGS_H_
#define _BIN_SETTINGS_H_

#include <vector>
#include <string>

typedef std::vector< std::string> 

struct  binSetting
{
	binSetting():showTray(0)
	{};

	int showTray;
	tVecRig vRigs;
};

#endif	//_BIN_SETTINGS_H_