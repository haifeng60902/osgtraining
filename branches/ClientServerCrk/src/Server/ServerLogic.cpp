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

void ServerLogic::Process()
{
	if (iResult==0)
	{
		bool bProc=true;
		while(bProc)
		{
			TCPStream* stream = pAcceptor->accept();
			if (stream)
			{
				int len=0;
				while ((len = stream->receive(inBuff, sizeof(inBuff))) > 0)
					//������ ����� ���������� �������
					m_EmulLogic.Accumulate(inBuff, len);

				//���������� ������� ������
				m_EmulLogic.Process();

				//��������� ��� �������� � ����
				const char* pRes=m_EmulLogic.GetResult(&len);

				stream->send(pRes, len);

				delete stream;
			}
			else
				bProc=false;

			bProc=bProc&&KeyPressDetect();
		}
	}
}

void ServerLogic::Close()
{
	delete pAcceptor;
}

bool ServerLogic::KeyPressDetect()
{
	//����������� ������� �� �������
	bool bStop = false;

	char cT('_');
	if (kbhit())
		cT = getch();

	if ( cT == 27 )
		bStop = true;

	return bStop;
}