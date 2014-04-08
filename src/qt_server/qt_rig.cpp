#include "qt_rig.h"

#include <QMessageBox>

qt_rig::qt_rig(const std::string sConf, QWidget *parent)
	: QDialog(parent)
{
	luaParseConf luaConf;
	luaConf.parse(sConf.c_str(), &settings);

	setWindowTitle("Rigs Monitor");

	mainLayout=new QVBoxLayout;
	setLayout(mainLayout);
	
	addTabs();
	//addGroups();

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

	connect(&tcpServer, SIGNAL(newConnection()),
		this, SLOT(acceptConnection()));

	 if(!tcpServer.listen(QHostAddress::Any, 9800))
	 {
		 int a=1;
	 }
}

qt_rig::~qt_rig()
{

}

void qt_rig::addTabs()
{
	tabWidget = new QTabWidget(this);

	mainLayout->addWidget(tabWidget);

	rigInfo.Init(settings);
	QWidget* rigInfoWidget=rigInfo.GetWidget();

	rigSett.Init(settings);
	QWidget* rigSettWidget=rigSett.GetWidget();

	tabWidget->addTab(rigInfoWidget, tr("Rigs info"));
	tabWidget->addTab(rigSettWidget, tr("Settings"));
}

void qt_rig::timerTick()
{
	static int it=0;
	++it;
}

void qt_rig::acceptConnection()
{
	tcpServerConnection = tcpServer.nextPendingConnection();
	
	connect(tcpServerConnection, SIGNAL(readyRead()),
		this, SLOT(updateServer()));
	connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void qt_rig::updateServer()
{
	int bytesReceived = (int)tcpServerConnection->bytesAvailable();
	QString sR = tcpServerConnection->readAll();

	std::string sRa=sR.toStdString();
	setWindowTitle(sRa.c_str());

	std::string sReq("Success123!");
	tcpServerConnection->write(sReq.c_str());

	tcpServerConnection->close();
}

void qt_rig::displayError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QTcpSocket::RemoteHostClosedError)
		return;

	QMessageBox::information(this, tr("Network error"),
		tr("The following error occurred: %1.")
		.arg(tcpServerConnection->errorString()));

	tcpServer.close();
}