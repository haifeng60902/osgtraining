#include "PassChkLogic.h"

#include <iostream>

#include "Tcp/TCPStream.h"
#include "Unicode/UnicodeOnOff.h"
#include "binState.h"

PassChkLogic::PassChkLogic()
{

}

PassChkLogic::~PassChkLogic()
{

}

bool PassChkLogic::Init(const std::string& sNode, const std::string& sCrypto)
{
	//set node name
	this->sNode=sNode;

	m_BtcdLauncher.Init(sCrypto);

	//first time init output buffer
	FirstTimeInit();

	//is bitcoind lunch like a daemon?
	bool bRes=BtcdDetect();

	return bRes;
}

void PassChkLogic::FirstTimeInit()
{
	//first time init output buffer
	int x=sNode.size();
	outBuff[0]=x;
	memcpy(&outBuff[1], sNode.c_str(), x);
	++x;
	memset(&outBuff[x], 0, MAX_LEN_PASS);
	x+=MAX_LEN_PASS;
	outBuff[x]=-1;
	++x;
	outSize=x;
}

void PassChkLogic::FillOutBuffer(int iRes)
{
	//fill output buffer with results
	int x=sNode.size()+1;
	memcpy(&outBuff[x], cChain, MAX_LEN_PASS);
	x+=MAX_LEN_PASS;
	outBuff[x]=iRes;

	std::cout<<"Result:"<<iRes<<std::endl;
}

const char* PassChkLogic::GetResult(int* pSize)
{
	//get result for network sending
	(*pSize)=outSize;
	return outBuff;
}

void PassChkLogic::Accumulate(TCPStream* stream)
{
	//wait server response
	inSize=0;
	bool bProc=true;
	while(bProc)
	{
		int len=stream->receive(inBuff, sizeof(inBuff));
		if (len)
		{
			inSize=len;

			//данные получены, можно выходить
			bProc=false;
		}
	}
}

int PassChkLogic::Process()
{
	//process income data

	tVecWStr vPass,  vCons;
	
	//restore data from input buffer
	RestoreRawMemory(vPass, vCons);

	//try unlock wallet
	int iRes=TryPass(vPass, vCons);

	if (iRes>-1)
		//fill output buffer with results
		FillOutBuffer(iRes);

	return iRes;
}

void PassChkLogic::RestoreRawMemory(tVecWStr& vPass, tVecWStr& vCons)
{
	//restore output buffer(for test purpose)
	int iPassInOneMsg=inBuff[0];
	int iMaxLenPass=inBuff[1];
	
	memcpy(cChain, &inBuff[2], MAX_LEN_PASS);
	int x=MAX_LEN_PASS+2;

	for (int i=0;i<iPassInOneMsg;++i)
	{
		std::wstring wPass;
		int s=inBuff[x];
		wPass.resize(s);
		++x;
		for (int j=0;j<s;++j)
		{
			wchar_t* wC=(wchar_t*)(&inBuff[x]);
			wPass[j]=(*wC);
			x+=sizeof(wchar_t);
		}
		vPass.push_back(wPass);
	}

	for (int i=0;i<iPassInOneMsg;++i)
	{
		std::wstring wCons;
		int s=inBuff[x];
		wCons.resize(s);
		++x;
		for (int j=0;j<s;++j)
		{
			wchar_t* wC=(wchar_t*)(&inBuff[x]);
			wCons[j]=(*wC);
			x+=sizeof(wchar_t);
		}
		vCons.push_back(wCons);
	}
}

int PassChkLogic::TryPass(const tVecWStr& vPass, const tVecWStr& vCons)
{
	//try unlock wallet
	
	bool bProcess=true;
	int i=0;
	while (bProcess)
	{
		{
			UnicodeOnOff on;
			std::wcout<<vCons[i]<<std::endl;
		}

		pswTry tryStatus=m_BtcdLauncher.Process(vPass[i]);

		switch (tryStatus)
		{
		case pswNext:
			++i;
			break;
		case pswSuccess:
			{
				UnicodeOnOff on;
				std::wcout<<L"Success:<"<<vCons[i]<<L">"<<std::endl;
			}
			return i+1;
			break;
		case pswError:
			return -1;
			break;
		}
		if (i>=vPass.size())
			bProcess=false;
	}
	return 0;
}

bool PassChkLogic::BtcdDetect()
{
	//is bitcoind lunch like a daemon?
	bool bRes=true;
	while(true)
	{
		pswTry tryStatus=m_BtcdLauncher.Process(L"1a2b3d");
		if (tryStatus==pswError)
		{
			bRes=false;
			break;
		}

		if (tryStatus!=pswTryAgain)
			break;
	}
	return bRes;
}