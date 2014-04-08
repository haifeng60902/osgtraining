#include "netFeedback.h"

netFeedback::netFeedback()
{

}

netFeedback::~netFeedback()
{

}

void netFeedback::init(const std::string& server, int port)
{
	sHostServer=server;
	iPortServer=port;
	connect(&tcpClientServer, SIGNAL(connected()),this, SLOT(connected()));
	connect(&tcpClientServer, SIGNAL(readyRead()),this, SLOT(readyRead()));
	connect(&tcpClientServer, SIGNAL(hostFound()),this, SLOT(hostFound()));
}

//send to server
void netFeedback::send(const std::string& msg)
{
	sMsg=msg;
	tcpClientServer.connectToHost(sHostServer.c_str(), iPortServer, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
}

void netFeedback::connected()
{
	tcpClientServer.write(sMsg.c_str());
}

void netFeedback::readyRead()
{
	QString sR= tcpClientServer.readAll();

	std::string sRa=sR.toStdString();
	tcpClientServer.disconnectFromHost();
}

void netFeedback::hostFound()
{
	
}