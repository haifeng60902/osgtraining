#include "PassGen.h"

#include <iostream>
#include <windows.h>

PassGen::PassGen()
{

}

PassGen::~PassGen()
{

}

void PassGen::Init(const std::wstring& wConf)
{
	//открыть файл с символами перебора
	
	//load config
	LoadConf(wConf);

	//zero memory
	for (int i=0;i<MAX_PASS;++i)
		iPassState[i]=0;
}

std::wstring PassGen::GenNextPass()
{
	//generate next password
	if (wCons.empty())
		return std::wstring();

	bool bCont=true;
	int i=0;
	while (bCont)
	{
		++iPassState[i];
		bCont=false;

		if (iPassState[i]>wCons.size())
		{
			//overflow
			iPassState[i]=1;
			++i;
			bCont=true;
		}
	}
	
	std::wstring wPassRes;
	std::wstring wConsRes;
	for (int i=0;i<MAX_PASS;++i)
	{
		int j=iPassState[i]-1;
		if (j>-1)
		{
			int k=vConvert[j].pos;
			wPassRes=wPassRes+wPass[k];
			if(vConvert[j].num>1)
				wPassRes=wPassRes+wPass[k+1];

			wConsRes=wConsRes+wCons[j];
		}
	}

	std::wcout<<wConsRes<<std::endl;

	return wPassRes;
}

void PassGen::SaveSuccessPass(const std::wstring& wConf)
{
	//save success password
	std::wstring wConsRes;
	for (int i=0;i<MAX_PASS;++i)
	{
		int j=iPassState[i]-1;
		if (j>-1)
			wConsRes=wConsRes+wCons[j];
	}

	FILE * pzInFile;
	_wfopen_s( &pzInFile, wConf.c_str(), L"w" );
	if (pzInFile)
	{
		fprintf(pzInFile, "%s", wConsRes.c_str());
		fclose(pzInFile);
	}
	else
	{
		std::wcout<<"Error create succes file: "<<wConf.c_str()<<std::endl;
	}
}

void PassGen::Close()
{

}

void PassGen::LoadConf(const std::wstring& wConf)
{
	//load config

	FILE * pzInFile;
	char   sUtf8[8192];

	wchar_t wsUtf16p[8192];//для запуска
	wchar_t wsUtf16c[8192];//для вывода в консоль

	_wfopen_s( &pzInFile, wConf.c_str(), L"r" );

	if (pzInFile)
	{
		char * pcDst = sUtf8;

		size_t uiRead;
		while( uiRead = fread_s( pcDst, sizeof( sUtf8 ), 1, 1, pzInFile ) )
			pcDst += uiRead;

		size_t uiLen = pcDst - sUtf8;
		sUtf8[uiLen] = 0;

		MultiByteToWideChar(CP_THREAD_ACP, 0, sUtf8, 8192, wsUtf16p, 8192 ); // convert for password
		MultiByteToWideChar(CP_UTF8, 0, sUtf8, 8192, wsUtf16c, 8192 ); // convert for console

		wPass=wsUtf16p;
		wCons=wsUtf16c;
		fclose(pzInFile);

		int j=0;
		vConvert.resize(wCons.size());
		for(int i=0;i<wCons.size();++i)
		{
			if (wPass[j]!=wCons[i])
			{
				vConvert[i].pos=j;
				vConvert[i].num=2;
				j+=2;
			}
			else
			{
				vConvert[i].pos=j;
				++j;
			}
		}

	}
}