#include "PassGen.h"

#include <iostream>
#include <fstream>
#include <fstream>
#include <windows.h>

#include "Unicode/UnicodeOnOff.h"

PassGen::PassGen()
{
	iAutosave=0;
	bFirstTime=true;
}

PassGen::~PassGen()
{

}

void PassGen::Init(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase,
				   int iPASS_IN_ONE_MSG)
{
	m_iPASS_IN_ONE_MSG=iPASS_IN_ONE_MSG;

	//zero memory
	for (int i=0;i<MAX_LEN_PASS;++i)
		cPassState[i]=0;

	//load config
	LoadConf(wConf, &wPass, &wCons, &vConvert);

	//load phrase
	LoadConf(wPhrase, &wPhrasePass, &wPhraseCons, &vPhrareConv);

	wSave=wAutosave;

	//состояние из файла
	LoadState();
}

void PassGen::GenNextPass(std::wstring* pPass, std::wstring* pCons)
{
	//generate next password
	if (wCons.empty())
		return;

	if (iAutosave>=m_iPASS_IN_ONE_MSG)
	{
		//автосохранение состояния
		SaveState();
		iAutosave=0;
	}

	//если есть ключевая фраза то первый раз выдать только ее
	if ((bFirstTime)&&(!wPhraseCons.empty()))
	{
		UnicodeOnOff on;

		std::wcout<<wPhraseCons<<std::endl;
		bFirstTime=false;

		(*pPass)=wPhrasePass;
		(*pCons)=wPhraseCons;

		return ;
	}

	bool bCont=true;
	int i=0;
	while (bCont)
	{
		++cPassState[i];
		bCont=false;

		if (cPassState[i]>wCons.size())
		{
			//overflow
			cPassState[i]=1;
			++i;
			bCont=true;
		}
	}
	
	std::wstring wPassRes=wPhrasePass;
	std::wstring wConsRes=wPhraseCons;
	for (int i=0;i<MAX_LEN_PASS;++i)
	{
		int j=cPassState[i]-1;
		if (j>-1)
		{
			int k=vConvert[j].pos;
			wPassRes=wPassRes+wPass[k];
			if(vConvert[j].num>1)
				wPassRes=wPassRes+wPass[k+1];

			wConsRes=wConsRes+wCons[j];
		}
	}

	++iAutosave;

	(*pPass)=wPassRes;
	(*pCons)=wConsRes;
}

void PassGen::GenNextChainPass(std::wstring* pPass, std::wstring* pCons, char* pChain, bool bZero)
{
	//generate next password with separate chain
	if (wCons.empty())
		return;

	//если есть ключевая фраза то первый раз выдать только ее
	if ((bZero)&&(!wPhraseCons.empty()))
	{
		UnicodeOnOff on;
		std::wcout<<wPhraseCons<<std::endl;
		
		(*pPass)=wPhrasePass;
		(*pCons)=wPhraseCons;

		return ;
	}

	bool bCont=true;
	int i=0;
	while (bCont)
	{
		++pChain[i];
		bCont=false;

		if (pChain[i]>wCons.size())
		{
			//overflow
			pChain[i]=1;
			++i;
			bCont=true;
		}
	}

	std::wstring wPassRes=wPhrasePass;
	std::wstring wConsRes=wPhraseCons;
	for (int i=0;i<MAX_LEN_PASS;++i)
	{
		int j=pChain[i]-1;
		if (j>-1)
		{
			int k=vConvert[j].pos;
			wPassRes=wPassRes+wPass[k];
			if(vConvert[j].num>1)
				wPassRes=wPassRes+wPass[k+1];

			wConsRes=wConsRes+wCons[j];
		}
	}

	(*pPass)=wPassRes;
	(*pCons)=wConsRes;
}

bool PassGen::ZeroChk(char* pDest)
{
	//is all elements zero
	bool bZero=true;
	for (int i=0;i<MAX_LEN_PASS;++i)
		if (pDest[i]>0)
			bZero=false;
	return bZero;
}

void PassGen::SaveSuccessPass(const std::wstring& wConf)
{
	//save success password

	if (wConf.empty())
		return;

	std::wstring wConsRes;
	for (int i=0;i<MAX_LEN_PASS;++i)
	{
		int j=cPassState[i]-1;
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
		UnicodeOnOff on;
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

	std::ofstream ofs;
	ofs.open(wSave, std::ios::out);
	if (ofs.is_open())
	{
		for (int i=0;i<MAX_LEN_PASS;++i)
		{
			ofs<<cPassState[i];
			ofs<<" ";
		}
		ofs.close();
	}
}

void PassGen::LoadState()
{
	//состояние из файла
	if (wSave.empty())
		return;

	std::ifstream ifs(wSave,std::ios::in|std::ios::binary);

	if (ifs.is_open())
	{
		char cP=0;
		int i=0;
		std::cout<<"Load autosave: ";
		while(!ifs.eof())
		{
			if (i>=MAX_LEN_PASS)
				break;

			ifs>>cP;
			cPassState[i]=cP;
			++i;
			std::cout<<(int)cP<<" ";
		}
		std::cout<<std::endl;
		ifs.close();
		std::cout<<std::endl;
	}
}

void PassGen::GetPassState(char* pDest)
{
	//get password state
	memcpy(pDest, cPassState, MAX_LEN_PASS);
}