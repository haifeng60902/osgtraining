#include "qt_diag.h"

#include "QtHlp/QtHlp.h"

qt_diag::qt_diag(const std::string& sHost, QWidget *parent):QDialog(parent),
	host(sHost)
{
	diagLayout=new QVBoxLayout;
	setLayout(diagLayout);
	setVisible(true);
	bConnect=false;
	bConn2Host=true;

	summaryLabel=new QLabel;
	diagLayout->addWidget(summaryLabel);

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

	connect(&tcpClientServer, SIGNAL(connected()),this, SLOT(connectedClient()));
	connect(&tcpClientServer, SIGNAL(readyRead()),this, SLOT(readyReadClient()));
	connect(&tcpClientServer, SIGNAL(hostFound()),this, SLOT(hostFoundClient()));
	connect(&tcpClientServer, SIGNAL(disconnected()),this, SLOT(disconnectedClient()));

	tcpClientServer.connectToHost(host.c_str(), 9900, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
}

qt_diag::~qt_diag()
{

}

void qt_diag::timerTick()
{
	static int i=0;
	std::string sC="No";
	if (bConnect)
	{
		++i;
		sC="Yes";
		writeMsg();
	}

	sC=sC+":"+std::to_string(i)+"|"+sRead+"("+sLocHost+")";
	summaryLabel->setText(sC.c_str());

	if (!bConn2Host)
	{
		tcpClientServer.connectToHost(host.c_str(), 9900, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
		bConn2Host=true;
	}
}

void qt_diag::connectedClient()
{
	bConnect=true;
}

void qt_diag::writeMsg()
{
	std::string sS;
	getRndStr(&sS);
	QtHlp::WriteStr(&tcpClientServer, sS);
}

void qt_diag::readyReadClient()
{
	QtHlp::GetStr(&tcpClientServer,&sRead,&sLocHost);
}

void qt_diag::hostFoundClient()
{
	
}

void qt_diag::disconnectedClient()
{
	bConnect=false;
	bConn2Host=false;
}

//fill random string
quint16 qt_diag::getRndStr(std::string* s)
{
	quint16 iSize=1024+1024*(float)rand()/(float)RAND_MAX;
	s->resize(iSize);
	for (int i=0;i< iSize;++i)
		s->at(i)=64+24*(float)rand()/(float)RAND_MAX;

	return iSize;
}