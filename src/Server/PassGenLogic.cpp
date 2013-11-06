#include "PassGenLogic.h"

#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>

PassGenLogic::PassGenLogic()
{
	inSize=0;
	outSize=0;
	iCurResult=-1;
}

PassGenLogic::~PassGenLogic()
{

}

void PassGenLogic::InitPassLogic(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase)
{
	//pass generator logic init
	m_PassGen.Init(wConf, wAutosave, wPhrase);
}

void PassGenLogic::Accumulate(const char* pBuff, int iSize)
{
	//прием данных
	inSize=0;
	memcpy(&inBuff[inSize], pBuff, iSize);
	inSize+=iSize;
}

bool PassGenLogic::Process()
{
	//обработать входные данные
	//read node name
	int posChain=DetectName(0);

	//read chain state
	int posState=DetectChainState(posChain);

	//read result
	DetectResult(posState);

	//analayse data from network
	bool bRes=Analyse();

	return bRes;
}

const char* PassGenLogic::GetResult(int *pSize)
{
	//результат для отправки в сеть
	(*pSize)=outSize;
	return outBuff;
}

int PassGenLogic::DetectName(int pos)
{
	//read node name
	unsigned char ucSize=inBuff[pos];
	char cBuff[255];
	memcpy(cBuff, &inBuff[1], ucSize);
	cBuff[ucSize]=0;

	//string contain node name
	sNode=cBuff;

	return ucSize+1;
}

int PassGenLogic::DetectChainState(int pos)
{
	//read chain state
	memcpy(curChain, &inBuff[pos], MAX_LEN_PASS);
	return MAX_LEN_PASS+pos;
}

int PassGenLogic::DetectResult(int pos)
{
	//read result
	iCurResult=inBuff[pos];
	return pos+1;
}

bool PassGenLogic::Analyse()
{
	//analayse data from network
	bool bRes=false;
	switch (iCurResult)
	{
	case -1:
		//first client connect
		ClientConnect();
		break;
	case 0:
		//client do not find password
		ClientDoNotFindPass();

		//client connect
		ClientConnect();
		break;
	default:
		//the password is find
		Success();
		bRes=true;
		break;
	}

	return bRes;
}

void PassGenLogic::ClientConnect()
{
	//first client connect
	m_PassGen.GetPassState(curChain);

	//for output Unicode text purpose
	_setmode(_fileno(stdout), _O_WTEXT);	//_O_WTEXT	_O_TEXT

	//generate file name
	std::string sFile=GenFileName(curChain);

	tVecWStr vPass;
	tVecWStr vCons;
	for (int i=0;i<PASS_IN_ONE_MSG;++i)
	{
		std::wstring wPass, wCons;
		m_PassGen.GenNextPass(&wPass, &wCons);

		vPass.push_back(wPass);
		vCons.push_back(wCons);
	}

	//fill output buffer
	FillOutBuff(curChain, vPass, vCons);

	//check result code-decode
	CheckCodeDecode(vPass, vCons);

	//write to file network output buffer
	Write2File(sFile);

	//for output ansi text purpose
	_setmode(_fileno(stdout), _O_TEXT);	//_O_WTEXT	_O_TEXT
}

void PassGenLogic::ClientDoNotFindPass()
{
	//client do not find password
	
	//generate file name
	std::string sFile=GenFileName(curChain);

	bool bFile=false;
	{
		std::ifstream os;
		os.open(sFile.c_str(), std::ios::in | std::ios::binary);
		if (os.is_open())
		{
			bFile=true;
			os.close();
		}
	}

	if (bFile)
		//file is exist, remove it
			remove(sFile.c_str());
	else
		std::cout<<"Error: "<<sFile<<" file do not found"<<std::endl;
}

void PassGenLogic::CheckCodeDecode(const tVecWStr& vPass, const tVecWStr& vCons)
{
	//check result code-decode
	tVecWStr vPassChk;
	tVecWStr vConsChk;
	
	//restore output buffer
	RestoreRawMemory(vPassChk, vConsChk);

	for (int i=0;i<PASS_IN_ONE_MSG;++i)
	{
		if (vPass[i]!=vPassChk[i])
			std::wcout<<L"Error Pass Check"<<i<<L" "<<vPass[i]<<"!="<<vPassChk[i]<<std::endl;

		if (vCons[i]!=vConsChk[i])
			std::wcout<<L"Error Cons Check"<<i<<L" "<<vCons[i]<<"!="<<vConsChk[i]<<std::endl;
	}
}

void PassGenLogic::FillOutBuff(char* pChain, const tVecWStr& vPass, const tVecWStr& vCons)
{
	//fill output buffer
	outBuff[0]=PASS_IN_ONE_MSG;
	outBuff[1]=MAX_LEN_PASS;
	for (int i=0;i<MAX_LEN_PASS;++i)
		outBuff[2+i]=pChain[i];

	int x=MAX_LEN_PASS+2;
	for (int i=0;i<PASS_IN_ONE_MSG;++i)
	{
		int s=vPass[i].size();
		int ws=sizeof(wchar_t);
		outBuff[x]=s;
		++x;
		memcpy(&outBuff[x], vPass[i].c_str(), s*ws);
		x+=s*ws;
	}

	for (int i=0;i<PASS_IN_ONE_MSG;++i)
	{
		int s=vCons[i].size();
		int ws=sizeof(wchar_t);
		outBuff[x]=s;
		++x;
		memcpy(&outBuff[x], vCons[i].c_str(), s*ws);
		x+=s*ws;
	}
	outSize=x;
}

void PassGenLogic::RestoreRawMemory(tVecWStr& vPassChk, tVecWStr& vConsChk)
{
	//restore output buffer(for test purpose)
	int iPassInOneMsg=outBuff[0];
	int iMaxLenPass=outBuff[1];
	char cChain[MAX_LEN_PASS];
	memcpy(cChain, &outBuff[2], MAX_LEN_PASS);
	int x=MAX_LEN_PASS+2;
	
	for (int i=0;i<PASS_IN_ONE_MSG;++i)
	{
		std::wstring wPass;
		int s=outBuff[x];
		wPass.resize(s);
		++x;
		for (int j=0;j<s;++j)
		{
			wchar_t* wC=(wchar_t*)(&outBuff[x]);
			wPass[j]=(*wC);
			x+=sizeof(wchar_t);
		}
		vPassChk.push_back(wPass);
	}

	for (int i=0;i<PASS_IN_ONE_MSG;++i)
	{
		std::wstring wCons;
		int s=outBuff[x];
		wCons.resize(s);
		++x;
		for (int j=0;j<s;++j)
		{
			wchar_t* wC=(wchar_t*)(&outBuff[x]);
			wCons[j]=(*wC);
			x+=sizeof(wchar_t);
		}
		vConsChk.push_back(wCons);
	}
}

std::string PassGenLogic::GenFileName(char* pChain)
{
	//generate file name
	_Longlong iV=pChain[0];
	std::string sName=std::to_string(iV);
	for (int i=1;i<MAX_LEN_PASS;++i)
	{
		_Longlong iV=pChain[i];
		sName=sName+"_"+std::to_string(iV);
	}
	sName=sName+".cin";

	return sName;
}

void PassGenLogic::TestLogic()
{
	//debug logic
	TestFillInBuff();

	//process income data
	Process();
}

void PassGenLogic::TestFillInBuff()
{
	//debug logic
	inBuff[0]=3;
	inBuff[1]='a';
	inBuff[2]='b';
	inBuff[3]='c';
	for (int i=0;i<MAX_LEN_PASS;++i)
		inBuff[4+i]=0;
	inBuff[4+MAX_LEN_PASS]=-1;
	inSize=4+MAX_LEN_PASS+1;
}

void PassGenLogic::Write2File(const std::string& sFile)
{
	//write to file network output buffer
	std::ofstream os;
	os.open(sFile.c_str(), std::ios::out | std::ios::binary);
	os.write(outBuff, outSize);
	os.close();
}

void PassGenLogic::Success()
{
	//the password is find
	std::wstring wPass,wCons;
	m_PassGen.GetCurrentPass(curChain, iCurResult, &wPass, &wCons);
}