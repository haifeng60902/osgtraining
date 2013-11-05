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
	//������� ���� � ��������� ��������
	
	//zero memory
	for (int i=0;i<MAX_LEN_PASS;++i)
		cPassState[i]=0;

	//load config
	LoadConf(wConf, &wPass, &wCons, &vConvert);

	//load phrase
	LoadConf(wPhrase, &wPhrasePass, &wPhraseCons, &vPhrareConv);

	wSave=wAutosave;

	//��������� �� �����
	LoadState();
}

void PassGen::GenNextPass(std::wstring* pPass, std::wstring* pCons)
{
	//generate next password
	if (wCons.empty())
		return;

	if (iAutosave>AUTO_SAVE)
	{
		//�������������� ���������
		SaveState();
		iAutosave=0;
	}

	//���� ���� �������� ����� �� ������ ��� ������ ������ ��
	if ((bFirstTime)&&(!wPhraseCons.empty()))
	{
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

	std::wcout<<wConsRes<<std::endl;

	++iAutosave;

	(*pPass)=wPassRes;
	(*pCons)=wConsRes;
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
		std::wcout<<"Error create succes file: "<<wConf.c_str()<<std::endl;
	}
}

void PassGen::Close(bool bSave)
{
	//�������������� ���������
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

	wchar_t wsUtf16p[8192];//��� �������
	wchar_t wsUtf16c[8192];//��� ������ � �������

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
	//�������������� ���������
	if (wSave.empty())
		return;

	std::wofstream ofs(wSave);
	if (ofs.is_open())
	{
		for (int i=0;i<MAX_LEN_PASS;++i)
		{
			ofs<<cPassState[i];
			ofs<<L" ";
		}
		ofs.close();
	}
}

void PassGen::LoadState()
{
	//��������� �� �����
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
			cPassState[i]=iP;
			++i;
			std::wcout<<iP<<" ";
		}
		ifs.close();
		std::wcout<<std::endl;
	}
}

void PassGen::GetPassState(char* pDest)
{
	//get password state
	memcpy(pDest, cPassState, MAX_LEN_PASS);
}