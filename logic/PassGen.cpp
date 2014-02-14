#include "PassGen.h"

#include <iostream>
#include <fstream>
#include <fstream>
#include <windows.h>

#define AUTO_SAVE 30

PassGen::PassGen()
{
	iAutosave=0;
	bFirstTime=true;
}

PassGen::~PassGen()
{

}

void PassGen::Init(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase)
{
	//открыть файл с символами перебора
	
	//zero memory
	for (int i=0;i<MAX_PASS;++i)
		iPassState[i]=0;

	//load config
	LoadConf(wConf, &wPass, &wCons, &vConvert);

	//load phrase
	LoadConf(wPhrase, &wPhrasePass, &wPhraseCons, &vPhrareConv);

	wSave=wAutosave;

	//состояние из файла
	LoadState();
}

std::wstring PassGen::GenNextPass()
{
	//generate next password
	if (!wvVocab.empty())
		return GetNextVocab();

	if (wCons.empty())
		return std::wstring();

	if (iAutosave>AUTO_SAVE)
	{
		//автосохранение состояния
		SaveState();
		iAutosave=0;
	}

	//если есть ключевая фраза то первый раз выдать только ее
	if ((bFirstTime)&&(!wPhraseCons.empty()))
	{
		std::wcout<<wPhraseCons<<std::endl;
		bFirstTime=false;
		return wPhrasePass;
	}

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
	
	std::wstring wPassRes=wPhrasePass;
	std::wstring wConsRes=wPhraseCons;
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

	++iAutosave;

	return wPassRes;
}

void PassGen::SaveSuccessPass(const std::wstring& wConf)
{
	//save success password

	if (wConf.empty())
		return;

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

void PassGen::Close(bool bSave)
{
	//автосохранение состояния
	if (bSave)
		SaveState();
}

void PassGen::LoadConf(const std::wstring& wConf, std::wstring* pPass, std::wstring* pCons, tVecConv *pConv)
{
	//load config

	if (wConf.empty())
		return;

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

		(*pPass)=wsUtf16p;
		(*pCons)=wsUtf16c;
		fclose(pzInFile);

		int j=0;
		pConv->resize(pCons->size());
		for(int i=0;i<pCons->size();++i)
		{
			if ((*pPass)[j]!=(*pCons)[i])
			{
				(*pConv)[i].pos=j;
				(*pConv)[i].num=2;
				j+=2;
			}
			else
			{
				(*pConv)[i].pos=j;
				++j;
			}
		}
	}
}

void PassGen::SaveState()
{
	//автосохранение состояния
	if (wSave.empty())
		return;

	std::wofstream ofs(wSave);
	if (ofs.is_open())
	{
		for (int i=0;i<MAX_PASS;++i)
		{
			ofs<<iPassState[i];
			ofs<<L" ";
		}
		ofs.close();
	}
}

void PassGen::LoadState()
{
	//состояние из файла
	if (wSave.empty())
		return;

	std::wifstream ifs(wSave);

	if (ifs.is_open())
	{
		int iP=0;
		int i=0;
		std::wcout<<"Load autosave: ";
		while(!ifs.eof())
		{
			ifs>>iP;
			iPassState[i]=iP;
			++i;
			std::wcout<<iP<<" ";
		}
		ifs.close();
		std::wcout<<std::endl;
	}
}

void PassGen::InitVocab(const std::wstring& wVocab)
{
	std::wifstream ifs(wVocab);

	if (ifs.is_open())
	{
		int iP=0;
		int i=0;
		std::wcout<<"Load Vocab"<<std::endl;
		while(!ifs.eof())
		{
			std::wstring wPass;
			ifs>>wPass;
			wvVocab.push_back(wPass);
		}
		ifs.close();
	}
}

std::wstring PassGen::GetNextVocab()
{
	std::wstring sPass=wvVocab.back();
	std::wcout<<L"Try: "<<sPass<<std::endl;
	wvVocab.pop_back();
	return sPass;
}