#ifndef _BTCD_LAUNCHER_H_
#define _BTCD_LAUNCHER_H_

#include <string>
#include "binState.h"

class BtcdLauncher
{
public:
	BtcdLauncher();
	~BtcdLauncher();

	void Init(const std::wstring& wCrpt);

	//process next pass
	pswTry Process(const std::wstring& wPass);

private:
	std::wstring wCrypto;
};

#endif	//_BTCD_LAUNCHER_H_