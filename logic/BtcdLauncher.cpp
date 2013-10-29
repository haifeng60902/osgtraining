#include "BtcdLauncher.h"

#include <iostream>
#include <Windows.h>

BtcdLauncher::BtcdLauncher()
{

}

BtcdLauncher::~BtcdLauncher()
{

}

pswTry BtcdLauncher::Process(const std::wstring& wPass)
{
	//process next pass

	pswTry resTry=pswTry::pswNext;

	STARTUPINFOW si;

	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	std::wstring wFull=L" walletpassphrase "+wPass+L" 20";

	if(!CreateProcessW(L"bitcoind.exe", (LPWSTR)wFull.c_str(), NULL, NULL,FALSE, 0,NULL,NULL,&si,&pi ) )
		return pswTry::pswError;

	WaitForSingleObject( pi.hProcess, INFINITE );

	DWORD exitCode=0;

	// Get the exit code.
	GetExitCodeProcess(pi.hProcess, &exitCode);

	if (exitCode==0)
		resTry=pswTry::pswSuccess;
	else 
		if(exitCode==127)
			resTry=pswTry::pswError;

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread); 

	return resTry;
}