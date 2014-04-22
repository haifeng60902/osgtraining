#include "netFeedback.h"

#include "QtHlp/QtHlp.h"

#define MAX_MSG 4

netFeedback::netFeedback()
{
	iSend=0;
	iRecv=0;

	bConnect=false;
	bConn2Host=false;
}

netFeedback::~netFeedback()
{

}

void netFeedback::init(const std::string& server, int port, const std::string& user)
{
	sHostServer=server;
	iPortServer=port;
	sUser=user;
	vMsgOut.push_back(sUser);

	connect(&tcpClientServer, SIGNAL(connected()),this, SLOT(connectedClient()));
	connect(&tcpClientServer, SIGNAL(readyRead()),this, SLOT(readyReadClient()));
	connect(&tcpClientServer, SIGNAL(hostFound()),this, SLOT(hostFoundClient()));
	connect(&tcpClientServer, SIGNAL(disconnected()),this, SLOT(disconnectedClient()));

	bConnect=false;
	bConn2Host=true;

	tcpClientServer.connectToHost(sHostServer.c_str(), iPortServer, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
}

bool netFeedback::process()
{
	bool bRes=false;
	if(bConnect)
	{
		bRes=true;
		writeMsg();

	}
	if ((!bConn2Host)||(!bConnect))
	{
		tcpClientServer.connectToHost(sHostServer.c_str(), iPortServer, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
		bConn2Host=true;
	}

	return bRes;
}

void netFeedback::connectedClient()
{
	bConnect=true;
}

void netFeedback::readyReadClient()
{
	int bytesReceived = (int)tcpClientServer.bytesAvailable();
	QByteArray a=tcpClientServer.readAll();
	char* ad=a.data();

	QtHlp::GetStrs(bytesReceived,ad, &vMsgIn);
}

void netFeedback::hostFoundClient()
{
	
}

void netFeedback::push_msg(const std::string& msg)
{
	//store message for late processing
	vMsgOut.push_back(msg);
	if (vMsgOut.size()>MAX_MSG)
	{
		std::vector<std::string>::iterator it=vMsgOut.begin();
		++it;
		vMsgOut.erase(it);
	}
}

void netFeedback::disconnectedClient()
{
	bConnect=false;
	bConn2Host=false;
}

void netFeedback::writeMsg()
{
	std::vector<char> data;

	//convert from vector strings to char data
	QtHlp::WriteStrs(vMsgOut, data);

	//send to network
	tcpClientServer.write(&data[0],data.size());

	//empty message vector
	vMsgOut.clear();
}