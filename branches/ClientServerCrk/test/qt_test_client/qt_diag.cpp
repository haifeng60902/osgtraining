#include "qt_diag.h"

#include "QtHlp/QtHlp.h"

qt_diag::qt_diag(const std::string& sHost, int iTick, QWidget *parent):QDialog(parent),
	host(sHost)
{
	diagLayout=new QVBoxLayout;
	setLayout(diagLayout);
	setVisible(true);
	bConnect=false;
	bConn2Host=true;
	nMilliseconds=0;

	summaryLabel=new QLabel;
	diagLayout->addWidget(summaryLabel);

	timer = new QTimer(this);
	timer->start(iTick);
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
	static int iConn=0;
	std::string sC="No";
	if (bConnect)
	{
		++i;
		sC="Yes";
		writeMsg();
	}
	else
	{
		nMilliseconds=0;
		sRead.clear();
		sLocHost.clear();
	}

	sC=sC+":"+std::to_string(nMilliseconds)+"["+std::to_string(iConn)+"]|"+sRead+"("+sLocHost+")";
	summaryLabel->setText(sC.c_str());

	if ((!bConn2Host)||(!bConnect))
	{
		tcpClientServer.connectToHost(host.c_str(), 9900, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
		bConn2Host=true;
		++iConn;
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

	myTimer.start();
	QtHlp::WriteStr(&tcpClientServer, sS);
}

void qt_diag::readyReadClient()
{
	if (QtHlp::GetStr(&tcpClientServer,&sRead,&sLocHost))
	{
		nMilliseconds = myTimer.elapsed();
	}
}

void qt_diag::hostFoundClient()
{

}

void qt_diag::disconnectedClient()
{
	bConnect=false;
	bConn2Host=false;
	nMilliseconds=0;
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