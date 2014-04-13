#include "qt_diag.h"

qt_diag::qt_diag(QWidget *parent):QDialog(parent)
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

	tcpClientServer.connectToHost("192.168.1.2", 9900, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
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

	sC=sC+":"+std::to_string(i);
	summaryLabel->setText(sC.c_str());

	if (!bConn2Host)
	{
		tcpClientServer.connectToHost("192.168.1.2", 9900, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
		bConn2Host=true;
	}
}

void qt_diag::connectedClient()
{
	bConnect=true;
}

void qt_diag::writeMsg()
{
	tVecChar sS;
	quint16 iSize=getRndStr(&sS);
	tcpClientServer.write(&sS[0],iSize);
}

void qt_diag::readyReadClient()
{

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
quint16 qt_diag::getRndStr(tVecChar* s)
{
	quint16 iSize=1024+1024*(float)rand()/(float)RAND_MAX;
	s->resize(iSize);
	*(quint16*)(&((*s)[0]))=iSize;
	for (int i=2;i< iSize;++i)
		s->at(i)=64+24*(float)rand()/(float)RAND_MAX;

	return iSize;
}