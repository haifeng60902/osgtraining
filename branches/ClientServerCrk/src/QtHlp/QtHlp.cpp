#include "QtHlp/QtHlp.h"

bool QtHlp::ChkStr(QTcpSocket* sock, std::string* s)
{
	int bytesReceived = (int)sock->bytesAvailable();
	if (bytesReceived<2)
		return false;

	QByteArray a=sock->readAll();
	char* ad=a.data();
	quint16 si=*((quint16*)ad);
	if (si==bytesReceived)
	{
		*s=std::string(&ad[2], si-2);
	}

	return true;
}