#include "ProxyLogic.h"

#include "Tcp/TCPAcceptor.h"
#include "Tcp/TCPConnector.h"

ProxyLogic::ProxyLogic()
{
	m_iResult=0;
}

ProxyLogic::~ProxyLogic()
{
	delete m_pConnector;
	delete m_pAcceptor;
}

void ProxyLogic::Init(const std::string& sLocalAddress, const std::string& sRemoteAddress, int iLocalPort, int iRemotePort)
{
	m_sLocalAddress=sLocalAddress;
	m_sRemoteAddress=sRemoteAddress;
	m_iLocalPort=iLocalPort;
	m_iRemotePort=iRemotePort;

	m_pAcceptor=new TCPAcceptor(m_iLocalPort, m_sLocalAddress.c_str());
	m_iResult=m_pAcceptor->start();

	m_pConnector=new TCPConnector(false);
}

void ProxyLogic::Process()
{
	if (m_iResult==0)
	{
		while (true)
		{
			TCPStream* streamServer = m_pAcceptor->accept();
			if (streamServer)
			{
				int lenServer=0;
				lenServer = streamServer->receive(inBuffServer, sizeof(inBuffServer));

				TCPStream* streamClient = m_pConnector->connect(m_iRemotePort, m_sRemoteAddress.c_str());
				if (streamClient)
				{
					streamClient->send(inBuffServer, lenServer);

					int lenClient=Accumulate(streamClient);

					streamServer->send(inBuffClient, lenClient);

					delete streamClient;
				}

				delete streamServer;
			}
		}
	}
}

int ProxyLogic::Accumulate(TCPStream* streamClient)
{
	return 0;
}