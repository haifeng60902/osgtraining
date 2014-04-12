#include "qt_diag.h"

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

	tcpServer.listen(QHostAddress::Any, 9800);

}

qt_diag::~qt_diag()
{

}

void qt_diag::timerTick()
{
	static int i=0;
	summaryLabel->setText(std::to_string(i).c_str());
	++i;
}

void qt_diag::acceptConnection()
{
	binClient c;
	c.tcpClientSocket = tcpServer.nextPendingConnection();
	c.sClient=c.tcpClientSocket->peerAddress().toString().toStdString();
	c.clientLabel=new QLabel;
	c.clientLabel->setText(c.sClient.c_str());

	connect(c.tcpClientSocket, SIGNAL(readyRead()),
		this, SLOT(updateServer()));
	connect(c.tcpClientSocket, SIGNAL(disconnected()), 
		this, SLOT(clientDisconnected()));

	vClient.push_back(c);
}

void qt_diag::updateServer()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

}
void qt_diag::clientDisconnected()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

	if (!client)
		return;

	tVecClient::iterator it=vClient.begin();
	while (it!=vClient.end())
	{
		if (it->tcpClientSocket==client)
		{
			diagLayout->removeWidget(it->clientLabel);
			delete it->clientLabel;
			vClient.erase(it);
			it=vClient.end();
		}
		else
			++it;
	}

	client->deleteLater();
}