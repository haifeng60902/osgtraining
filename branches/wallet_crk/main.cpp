#include <iostream>
#include <string>

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include "logic/PassGen.h"
#include "logic/BtcdLauncher.h"

std::wstring wConf;
std::wstring wAutosave;
std::wstring wSuccess;

PassGen m_PassGen;
BtcdLauncher m_BtcdLauncher;

//определение нажатия на клавиши
bool KeyPressDetect();

int main(int argc, char** argv)
{
	//для отображения юникода в консоли
	_setmode(_fileno(stdout), _O_WTEXT);
	
	//имя конфига
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-config") == 0)
		{
			i++; if (i >= argc) break;
			std::string sConf = argv[i];
			wConf=std::wstring(sConf.begin(), sConf.end());
			continue;
		}
		else if (strcmp(argv[i], "-autosave") == 0)
		{
			i++; if (i >= argc) break;
			std::string sSave = argv[i];
			wAutosave=std::wstring(sSave.begin(), sSave.end());
			continue;
		}
		else if (strcmp(argv[i], "-success") == 0)
		{
			i++; if (i >= argc) break;
			std::string sConf = argv[i];
			wSuccess=std::wstring(sConf.begin(), sConf.end());
			continue;
		}
	}

	m_PassGen.Init(wConf, wAutosave);

	bool bStop = false;
	pswTry tryStatus=pswNext;
	int iCount=0;
	while(!bStop)
	{
		if (tryStatus==pswNext)
		{
			//generate next password
			std::wstring sPass=m_PassGen.GenNextPass();

			tryStatus=m_BtcdLauncher.Process(sPass);
		}

		if (tryStatus!=pswNext)
			bStop=true;

		//определение нажатия на клавиши
		bStop = bStop||KeyPressDetect();
		++iCount;
	}

	switch (tryStatus)
	{
	case pswTry::pswSuccess:
		m_PassGen.SaveSuccessPass(wSuccess);
		break;
	case pswTry::pswError:
		std::wcout<<"Error lunching program."<<std::endl;
		break;
	}

	bool bSave=false;
	if (iCount>1)
		bSave=true;
	m_PassGen.Close(bSave);
}

bool KeyPressDetect()
{
	//определение нажатия на клавиши
	bool bStop = false;
	
	char cT('_');
	if (kbhit())
		cT = getch();

	if ( cT == 27 )
		bStop = true;

	return bStop;
}