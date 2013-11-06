#include "ServerLogic.h"

#include <conio.h>
#include <iostream>

#include "Tcp/TCPAcceptor.h"

ServerLogic::ServerLogic():pAcceptor(NULL)
{
	iResult=0;
}

ServerLogic::~ServerLogic()
{

}

void ServerLogic::Init(int iPort, const std::string& sAddress)
{
	pAcceptor=new TCPAcceptor(iPort, sAddress.c_str());

	iResult=pAcceptor->start();
}

void ServerLogic::InitPassLogic(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase)
{
	//pass generator logic init
	m_PassGenLogic.InitPassLogic(wConf, wAutosave, wPhrase);
}

void ServerLogic::Process()
{
	if (iResult==0)
	{
		bool bExit=false;
		while(!bExit)
		{

#ifdef _DEBUG
			//m_PassGenLogic.TestLogic();
#endif
			TCPStream* stream = pAcceptor->accept();
			float fAcceptTime=m_Timer.GetTime();
			if (stream)
			{
				int len=0;
				len = stream->receive(inBuff, sizeof(inBuff));

				std::cout<<"net get "<<len<<std::endl;

				//данные могут приниматся частями
				m_PassGenLogic.Accumulate(inBuff, len);

				//обработать входные данные
				bExit=m_PassGenLogic.Process();

				//результат для отправки в сеть
				const char* pRes=m_PassGenLogic.GetResult(&len);

				stream->send(pRes, len);

				float fSendTime=m_Timer.GetTime();

				std::cout<<" ful:"<<(fSendTime-fAcceptTime)*1000.0f<<std::endl;

				delete stream;
			}
			else
				bExit=true;

			bExit=bExit||KeyPressDetect();
		}
	}
}

void ServerLogic::Close()
{
	delete pAcceptor;
}

bool ServerLogic::KeyPressDetect()
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