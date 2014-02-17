#include "PassGenLogic.h"

#include <iostream>
#include <fstream>

#include <windows.h>

#include "Unicode/UnicodeOnOff.h"

PassGenLogic::PassGenLogic()
{
	inSize=0;
	outSize=0;
	iCurResult=-1;
	m_fPrevTime=-1;
	m_iSumPass=0;
}

PassGenLogic::~PassGenLogic()
{

}

void PassGenLogic::InitPassLogic(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase
								 , float fTimeout, int iPASS_IN_ONE_MSG, bool bReverse, int iPASS_START_LEN)
{
	m_iPASS_IN_ONE_MSG=iPASS_IN_ONE_MSG;
	m_fTimeout=fTimeout;

	//pass generator logic init
	m_PassGen.Init(wConf, wAutosave, wPhrase, iPASS_IN_ONE_MSG, bReverse, iPASS_START_LEN);

	//read files from previous start
	ReadPreviousFiles();
}

void PassGenLogic::Accumulate(const char* pBuff, int iSize)
{
	//прием данных
	inSize=0;
	memcpy(&inBuff[inSize], pBuff, iSize);
	inSize+=iSize;
}

bool PassGenLogic::Process(float fTime)
{
	//обработать входные данные
	//read node name
	int posChain=DetectName(0);

	//read chain state
	int posState=DetectChainState(posChain);

	//read result
	DetectResult(posState);

	//analayse data from network
	bool bRes=Analyse(fTime);

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

bool PassGenLogic::Analyse(float fTime)
{
	//analayse data from network
	if (m_fPrevTime<0.0f)
		m_fPrevTime=fTime;

	bool bRes=false;
	switch (iCurResult)
	{
	case -1:
		//first client connect
		ClientConnect(fTime);
		break;
	case 0:
		//client do not find password
		ClientDoNotFindPass();

		//client connect
		ClientConnect(fTime);
		break;
	default:
		//the password is find
		Success();
		bRes=true;
		break;
	}

	//display performance
	LogPerfomance(fTime);

	m_fPrevTime=fTime;

	return bRes;
}

void PassGenLogic::ClientConnect(float fTime)
{
	//client connect

	//check files
	bool bFile=CheckMapFileTime(fTime);
	if (bFile)
		return;

	m_PassGen.GetPassState(curChain);

	//generate file name
	std::string sFile=GenFileName(curChain);

	tVecWStr vPass;
	tVecWStr vCons;
	for (int i=0;i<m_iPASS_IN_ONE_MSG;++i)
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

	//save to map
	m_mFileTime[sFile]=fTime;
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
	{
		//file is exist, remove it
		remove(sFile.c_str());
		tMapFileTime::iterator it=m_mFileTime.find(sFile);
		if (it!=m_mFileTime.end())
			m_mFileTime.erase(it);
		else
			std::cout<<"Remove file: "<<sFile<<" but record in map do not exist.\n";
	}
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

	for (int i=0;i<m_iPASS_IN_ONE_MSG;++i)
	{
		UnicodeOnOff on;

		if (vPass[i]!=vPassChk[i])
			std::wcout<<L"Error Pass Check"<<i<<L" "<<vPass[i]<<"!="<<vPassChk[i]<<std::endl;

		if (vCons[i]!=vConsChk[i])
			std::wcout<<L"Error Cons Check"<<i<<L" "<<vCons[i]<<"!="<<vConsChk[i]<<std::endl;
	}
}

void PassGenLogic::FillOutBuff(char* pChain, const tVecWStr& vPass, const tVecWStr& vCons)
{
	//fill output buffer
	outBuff[0]=m_iPASS_IN_ONE_MSG;
	outBuff[1]=MAX_LEN_PASS;
	for (int i=0;i<MAX_LEN_PASS;++i)
		outBuff[2+i]=pChain[i];

	int x=MAX_LEN_PASS+2;
	for (int i=0;i<m_iPASS_IN_ONE_MSG;++i)
	{
		int s=vPass[i].size();
		int ws=sizeof(wchar_t);
		outBuff[x]=s;
		++x;
		memcpy(&outBuff[x], vPass[i].c_str(), s*ws);
		x+=s*ws;
	}

	for (int i=0;i<m_iPASS_IN_ONE_MSG;++i)
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
	
	for (int i=0;i<m_iPASS_IN_ONE_MSG;++i)
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

	for (int i=0;i<m_iPASS_IN_ONE_MSG;++i)
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
	Process(0.0f);
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
	bool bZero=ZerroChainDetect(curChain);
	tVecWStr vPass,vCons;
	for (int i=0;i<iCurResult;++i)
	{
		std::wstring wPass,wCons;
		m_PassGen.GenNextChainPass(&wPass, &wCons, curChain, bZero);
		vPass.push_back(wPass);
		vCons.push_back(wCons);
		bZero=false;
	}

	{
		UnicodeOnOff on;
		std::wcout<<"Success password is:"<<vCons.back()<<std::endl;
	}

	FILE * pzInFile;
	_wfopen_s( &pzInFile, L"success.txt", L"w" );
	if (pzInFile)
	{
		fprintf(pzInFile, "%s", vCons.back().c_str());
		fclose(pzInFile);
	}
	else
	{
		UnicodeOnOff on;
		std::wcout<<"Error create succes file"<<std::endl;
	}
}

bool PassGenLogic::ZerroChainDetect(const char* pChain)
{
	//check zero chain
	bool bZero=true;
	for (int i=0;i<MAX_LEN_PASS;++i)
		if (pChain[i])
			bZero=false;
	return bZero;
}

void PassGenLogic::ReadPreviousFiles()
{
	//read files from previous start
	WIN32_FIND_DATA found;

	HANDLE hFind=FindFirstFile("*.cin", &found);
	if (hFind == INVALID_HANDLE_VALUE) 
		return;
	
	std::string sFile=found.cFileName;
	m_mFileTime[sFile]=-1.0f;
	while(true)
	{
		int chk=FindNextFile(hFind,&found);
		if (chk)
		{
			sFile=found.cFileName;
			m_mFileTime[sFile]=-1.0f;
		}
		else
			break;
	}
}

bool PassGenLogic::CheckMapFileTime(float fTime)
{
	//check files
	tMapFileTime::iterator it=m_mFileTime.begin();
	while (it!=m_mFileTime.end())
	{
		bool bRemove=false;
		float fChkTime=fTime-it->second;
		if (it->second<0.0)
			fChkTime=it->second;
		

		//files with below zero time have highest priority
		if ((fChkTime<0.0)||(fChkTime>m_fTimeout))
		{
			std::ifstream in(it->first, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				// get its size:
				in.seekg(0, std::ios::end);
				outSize = in.tellg();
				in.seekg (0, std::ios::beg);

				in.read(outBuff, outSize);
				in.close();
				std::cout<<"Timeout("<<fChkTime<<") Resend file:"<<it->first<<" \n";

				it->second=fTime;

				return true;
			}
			else
			{
				std::cout<<"Try to resend file: "<<it->first<<"("<<it->second<<") but file do not exist.\n";
				it=m_mFileTime.erase(it);
				bRemove=true;
			}
		}

		if (!bRemove)
			++it;
	}
	return false;
}

void PassGenLogic::LogPerfomance(float fTime)
{
	//display performance
	int iCTime=fTime/60.0f;
	int iPTime=m_fPrevTime/60.0f;
	if (iCTime!=iPTime)
	{
		m_iSumPass+=m_iPASS_IN_ONE_MSG;
		std::cout<<"Statistic: "<<m_iSumPass<<" per minute("<<fTime<<")\n";
		m_iSumPass=0;
	}
	else
	{
		m_iSumPass+=m_iPASS_IN_ONE_MSG;
	}
}