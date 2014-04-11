#include "netFeedback.h"

netFeedback::netFeedback()
{
	iSend=0;
	iRecv=0;
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
void netFeedback::send(const std::string& msg, int* send, int* recv)
{
	iSend=0;
	iRecv=0;
	sMsg=msg;
	tcpClientServer.connectToHost(sHostServer.c_str(), iPortServer, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);

	if(!tcpClientServer.waitForConnected(900))
		tcpClientServer.disconnectFromHost();

	(*send)=iSend;
	(*recv)=iRecv;
}

void netFeedback::connected()
{
	iSend=tcpClientServer.write(sMsg.c_str());
}

void netFeedback::readyRead()
{
	QString sR= tcpClientServer.readAll();

	std::string sRa=sR.toStdString();
	tcpClientServer.close();

	//iRecv=sRa.size();
	iRecv=1;
}

void netFeedback::hostFound()
{
	
}