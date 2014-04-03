#include "winCreateProcess.h"

#include <Windows.h>

winCreateProcess::winCreateProcess()
{

}

winCreateProcess::~winCreateProcess()
{

}

bool winCreateProcess::create(int i, binClient& client)
{
	bool bRes=true;
	char curdir[256];
	GetCurrentDirectory(sizeof(curdir),curdir);

	binCoin& coin=client.vCoins[i];
	binParam& param=client.mMiners[coin.sMiner];

	//path from lua conf
	SetCurrentDirectory(param.sPath.c_str());
	
	std::string sParam=coin.sMiner+" "+param.sParam;
	for (int j=0;j<coin.vPools.size();++j)
		sParam=sParam+" -o "+coin.vPools[j]+" -u "+client.sUser+" -p "+client.sPass;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	if(!CreateProcess(coin.sMiner.c_str(), (LPSTR)sParam.c_str(), NULL, NULL,FALSE, 0,NULL,NULL,&si,&pi))
		bRes=false;

	//restore def path
	SetCurrentDirectory(curdir);

	return bRes;
}