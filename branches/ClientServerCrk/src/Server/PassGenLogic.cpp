#include "PassGenLogic.h"

#include <vector>

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
	//����� ������
	memcpy(&inBuff[inSize], pBuff, iSize);
	inSize+=iSize;
}

void PassGenLogic::Process()
{
	//���������� ������� ������
	//read node name
	int posChain=DetectName(0);

	//read chain state
	int posState=DetectChainState(posChain);

	//read result
	DetectResult(posState);

	//analayse data from network
	Analyse();
}

const char* PassGenLogic::GetResult(int *pSize)
{
	//��������� ��� �������� � ����
	return 0;
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

void PassGenLogic::Analyse()
{
	//analayse data from network
	if (iCurResult<0)
	{
		//first client connect
		FirstClientConnect();
	}
}

#include <io.h>
#include <fcntl.h>
#include <iostream>
void PassGenLogic::FirstClientConnect()
{
	//first client connect
	m_PassGen.GetPassState(curChain);

	//generate file name
	std::string sFile=GenFileName(curChain);

	//��� ����������� ������� � �������
	_setmode(_fileno(stdout), _O_WTEXT);	//_O_WTEXT	_O_TEXT

	std::vector<std::wstring> vPass;
	std::vector<std::wstring> vCons;
	for (int i=0;i<PASS_IN_ONE_MSG;++i)
	{
		std::wstring wPass, wCons;
		m_PassGen.GenNextPass(&wPass, &wCons);

		vPass.push_back(wPass);
		vCons.push_back(wCons);

		std::wcout<<i<<" "<<wPass<<L" "<<wCons<<std::endl;
	}

	//��� ����������� ������� � �������
	_setmode(_fileno(stdout), _O_TEXT);	//_O_WTEXT	_O_TEXT
}

std::string PassGenLogic::GenFileName(char* pChain)
{
	//generate file name
	std::string sName;
	for (int i=0;i<MAX_LEN_PASS;++i)
	{
		_Longlong iV=pChain[i];
		sName=sName+std::to_string(iV);
	}

	return std::string();
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