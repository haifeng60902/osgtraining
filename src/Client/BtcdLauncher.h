#ifndef _BTCD_LAUNCHER_H_
#define _BTCD_LAUNCHER_H_

#include <string>
#include "binState.h"

class BtcdLauncher
{
public:
	BtcdLauncher();
	~BtcdLauncher();

	//process next pass
	pswTry Process(const std::wstring& wPass);
};

#endif	//_BTCD_LAUNCHER_H_