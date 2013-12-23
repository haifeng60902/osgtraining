#include "BatStart.h"

#include <iostream>
#include <Windows.h>

BatStart::BatStart()
{

}

BatStart::~BatStart()
{

}

void BatStart::Process(const tVecHosts& vHost)
{
	for (int i=0;i<vHost.size();++i)
	{
		if (vHost[i].bBat)
		{
			std::string sKillParam=" \\\\"+vHost[i].sHost+" -u "+vHost[i].sUser+" -p "+vHost[i].sPass+
				" cgminer.exe";
			std::string sExe="pskill.exe";
			PsStart(sExe, sKillParam);

			std::string sExecParam=" \\\\"+vHost[i].sHost+" -u "+vHost[i].sUser+" -p "+vHost[i].sPass+
				" -d -i -w "+vHost[i].sPath+" "+vHost[i].sPath+"\\"+vHost[i].sExec;
			
			std::string sExec="psexec.exe";
			PsStart(sExec, sExecParam);
		}
	}
}

void BatStart::PsStart(const std::string& sExe, const std::string& sParam)
{
	STARTUPINFO si;

	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	if(!CreateProcess(sExe.c_str(), (LPTSTR)sParam.c_str(), NULL, NULL,FALSE, 0,NULL,NULL,&si,&pi))
	{
		std::cout<<"Error: Cannot launch "<<sExe<<std::endl;
		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD exitCode=0;

	// Get the exit code.
	GetExitCodeProcess(pi.hProcess, &exitCode);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread); 
}