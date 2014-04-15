#include "QtHlp/QtHlp.h"

#include <vector>

bool QtHlp::GetStr(QTcpSocket* sock, std::string* s)
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
		*s=std::string(&ad[2], si-2);
		bRes=true;
	}

	return bRes;
}

void QtHlp::WriteStr(QTcpSocket* sock, const std::string& s)
{
	std::vector<char> data;
	data.resize(s.size()+2);
	*(quint16*)(&data[0])=s.size()+2;
	memcpy(&data[2],&s[0],s.size());
	sock->write(&data[0],data.size());
}