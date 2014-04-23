#ifndef _NET_FEEDBACK_H_
#define _NET_FEEDBACK_H_

#include <string>
#include <vector>

#include <QObject>
#include <QtNetwork>

#include "core/Parse/binMiner.h"

class netFeedback: public QObject
{
	Q_OBJECT

private slots:
	void connectedClient();
	void readyReadClient();
	void hostFoundClient();
	void disconnectedClient();

public:
	netFeedback();
	~netFeedback();

	void init(const std::string& server, int port, const std::string& user, int wait);

	bool process();

	//store message for late processing
	void push_msg(const std::string& msg);

private:

	void writeMsg();

	QTcpSocket tcpClientServer;

	std::string sHostServer;
	int iPortServer;
	std::string sUser;

	int iSend;
	int iRecv;
	bool bConnect;
	bool bConn2Host;
	bool bProcess;

	int iWait;

	std::vector<std::string> vMsgOut;
	std::vector<std::string> vMsgIn;
};

#endif	//_NET_FEEDBACK_H_