#ifndef _NET_FEEDBACK_H_
#define _NET_FEEDBACK_H_

#include <string>

#include <QObject>
#include <QtNetwork>

#include "binMiner.h"

class netFeedback: public QObject
{
	Q_OBJECT

private slots:
	void connected();
	void readyRead();
	void hostFound();

public:
	netFeedback();
	~netFeedback();

	void init(const std::string& server, int port);

	//send to server
	void send(const std::string& msg);

private:
	QTcpSocket tcpClientServer;

	std::string sHostServer;
	int iPortServer;
};

#endif	//_NET_FEEDBACK_H_