#include "BtcdLauncher.h"

#include <iostream>
#include <Windows.h>

#include "Unicode/UnicodeOnOff.h"

BtcdLauncher::BtcdLauncher()
{

}

BtcdLauncher::~BtcdLauncher()
{

}

void BtcdLauncher::Init(const std::string& sCrypto)
{
	wCrypto=std::wstring(sCrypto.begin(), sCrypto.end());
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

	if(!CreateProcessW((LPWSTR)wCrypto.c_str(), (LPWSTR)wFull.c_str(), NULL, NULL,FALSE, 0,NULL,NULL,&si,&pi))
	{
		UnicodeOnOff on;
		std::wcout<<"Error: Cannot launch "<<wCrypto<<std::endl;
		return pswError;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD exitCode=0;

	// Get the exit code.
	GetExitCodeProcess(pi.hProcess, &exitCode);

	{
		UnicodeOnOff on;
		std::wcout<<L"Exit code:"<<exitCode<<std::endl;
	}

	if (exitCode==0)
		resTry=pswSuccess;
	else
	{
		if (exitCode==87)
			resTry=pswTryAgain;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread); 

	return resTry;
}