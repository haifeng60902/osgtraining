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

	pswTry resTry=pswNext;

	STARTUPINFOW si;

	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	std::wstring wFull=L" walletpassphrase "+wPass+L" 20";

	if(!CreateProcessW(L"bitcoind.exe", (LPWSTR)wFull.c_str(), NULL, NULL,FALSE, 0,NULL,NULL,&si,&pi))
	{
		std::wcout<<"Error: Cannot launch bitcoind.exe"<<std::endl;
		return pswError;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD exitCode=0;

	// Get the exit code.
	GetExitCodeProcess(pi.hProcess, &exitCode);

	if (exitCode==0)
		resTry=pswSuccess;
	else
	{
		if ((exitCode!=14)&&(exitCode!=1)&&(exitCode!=87))
		{
			std::wcout<<L"Error code: "<<exitCode<<std::endl;
			resTry=pswTryAgain;
		}
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread); 

	return resTry;
}