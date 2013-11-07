#include "ClientLogic.h"

#include <conio.h>
#include <iostream>
#include "Tcp/TCPConnector.h"

ClientLogic::ClientLogic():pConnector(NULL)
{
	iSuccess=-1;
}

ClientLogic::~ClientLogic()
{

}

bool ClientLogic::Init(int iPort, const std::string& sAddress, const std::string& sNode)
{
	pConnector=new TCPConnector();
	this->iPort=iPort;
	this->sAddress=sAddress;
	this->sNode=sNode;
	
	bool bRes=m_PassChkLogic.Init(sNode);

	return bRes;
}

void ClientLogic::Process()
{
	bool bExit=false;
	while(!bExit)
	{
		float fConnectBegin=m_Timer.GetTime();
		TCPStream* stream = pConnector->connect(iPort, sAddress.c_str());
		if (stream)
		{
			int iSize=0;
			const char* pBuff=m_PassChkLogic.GetResult(&iSize);
			stream->send(pBuff, iSize);

			//wait server response
			m_PassChkLogic.Accumulate(stream);

			delete stream;

			float fAccumulateTime=m_Timer.GetTime();

			std::cout<<" ful:"<<(fAccumulateTime-fConnectBegin)*1000.0f<<" ";

			//process income data
			int iRes=m_PassChkLogic.Process();

			if (iRes<0)
				return;

			if (iRes>0)
				iSuccess=0;
		}
		else
			Sleep(1000);

		if (iSuccess>-1)
			++iSuccess;

		if (iSuccess>1)
			return;

		bExit=KeyPressDetect();
	}
}

void ClientLogic::Close()
{
	delete pConnector;
}

bool ClientLogic::KeyPressDetect()
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