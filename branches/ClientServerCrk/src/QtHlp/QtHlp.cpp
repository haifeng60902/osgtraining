#include "QtHlp/QtHlp.h"

#include <vector>
#include <QHostAddress>

bool QtHlp::GetStr(QTcpSocket* sock, std::string* str, std::string* loc)
{
	bool bRes=false;
	int bytesReceived = (int)sock->bytesAvailable();
	if (bytesReceived<2)
		return bRes;

	QByteArray a=sock->readAll();
	char* ad=a.data();
	quint16 si=*((quint16*)ad);
	if (si==bytesReceived)
	{
		char sL=ad[2];
		std::string s;
		*loc=std::string(&ad[3], sL);
	
		*str=std::string(&ad[3+sL], si-3-sL);
		bRes=true;
	}

	return bRes;
}

void QtHlp::WriteStr(QTcpSocket* sock, const std::string& s)
{
	std::vector<char> data;
	std::string sLoc=sock->localAddress().toString().toStdString();
	data.resize(s.size()+2+sLoc.size()+1);
	*(quint16*)(&data[0])=s.size()+2+sLoc.size()+1;
	data[2]=sLoc.size();
	memcpy(&data[3],&sLoc[0],sLoc.size());


	memcpy(&data[3+sLoc.size()],&s[0],s.size());
	sock->write(&data[0],data.size());
}

bool QtHlp::GetStrs(QTcpSocket* sock, std::vector<std::string>* vs)
{

	return true;
}

void QtHlp::WriteStrs(QTcpSocket* sock, const std::vector<std::string>& vs)
{
	int iSize=4+vs.size()*2;
	for (int i=0;i<vs.size();++i)
		iSize+=vs[i].size();
}