#include "qt_diag.h"

#include "QtHlp/QtHlp.h"

qt_diag::qt_diag(QWidget *parent):QDialog(parent)
{
	diagLayout=new QVBoxLayout;
	setLayout(diagLayout);
	setVisible(true);

	summaryLabel=new QLabel;
	diagLayout->addWidget(summaryLabel);

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

	connect(&tcpServer, SIGNAL(newConnection()),
		this, SLOT(acceptConnection()));

	tcpServer.listen(QHostAddress::Any, 9900);

}

qt_diag::~qt_diag()
{

}

void qt_diag::timerTick()
{
	static int i=0;
	summaryLabel->setText(std::to_string(i).c_str());
	++i;

	tMapClient::iterator it=mClient.begin();
	while (it!=mClient.end())
	{
		--it->second.iWait;
		if (it->second.iWait<1)
		{
			QTcpSocket* tcpClientSocket=it->first;
			QLabel* clientLabel=it->second.clientLabel;

			it=mClient.erase(it);

			diagLayout->removeWidget(clientLabel);
			delete clientLabel;
			//tcpClientSocket->deleteLater();
			tcpClientSocket->disconnectFromHost();
		}
		else
			++it;
	}
}

void qt_diag::acceptConnection()
{
	QTcpSocket* tcpClientSocket = tcpServer.nextPendingConnection();
	binClient& c=mClient[tcpClientSocket];

	c.sClient=tcpClientSocket->peerAddress().toString().toStdString();
	
	c.clientLabel=new QLabel;
	diagLayout->addWidget(c.clientLabel);
	c.clientLabel->setText(c.sClient.c_str());

	connect(tcpClientSocket, SIGNAL(readyRead()),
		this, SLOT(updateServer()));
	connect(tcpClientSocket, SIGNAL(disconnected()), 
		this, SLOT(clientDisconnected()));
}

void qt_diag::updateServer()
{
	QTcpSocket *tcpSocket= qobject_cast<QTcpSocket *>(sender());

	std::string sStr,sLocHost;
	if(QtHlp::GetStr(tcpSocket,&sStr,&sLocHost))
	{
		tMapClient::iterator itClient=mClient.find(tcpSocket);
		if (itClient!=mClient.end())
		{
			binClient& c=itClient->second;

			++c.iMsgClue;

			c.iWait=WAIT_DISCONECT;
			c.iMsgSize=sStr.size();
			++c.iMsgRead;

			std::string sSt=c.sClient+"("+sLocHost+"):"+std::to_string(c.iMsgRead)+","+std::to_string(c.iMsgClue)+","+std::to_string(c.iMsgSize);
			c.clientLabel->setText(sSt.c_str());

			c.iMsgClue=0;
			std::string sReq("Success=");
			sReq=sReq+std::to_string(c.iMsgSize);
			QtHlp::WriteStr(tcpSocket, sReq);
		}
	}
}

void qt_diag::clientDisconnected()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

	if (!client)
		return;

	tMapClient::iterator it=mClient.find(client);
	if (it!=mClient.end())
	{
		diagLayout->removeWidget(it->second.clientLabel);
		delete it->second.clientLabel;
		mClient.erase(it);
	}

	client->deleteLater();
}