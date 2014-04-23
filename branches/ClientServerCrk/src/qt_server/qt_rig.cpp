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
	
	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

	connect(&tcpServer, SIGNAL(newConnection()),
		this, SLOT(acceptConnection()));

	tcpServer.listen(QHostAddress::Any, settings.iPort);
}

qt_rig::~qt_rig()
{

}

void qt_rig::addTabs()
{
	tabWidget = new QTabWidget(this);

	mainLayout->addWidget(tabWidget);

	rigInfo.init(settings);
	QWidget* rigInfoWidget=rigInfo.getWidget();

	rigSett.Init(settings);
	QWidget* rigSettWidget=rigSett.GetWidget();

	tabWidget->addTab(rigInfoWidget, tr("Rigs info"));
	tabWidget->addTab(rigSettWidget, tr("Settings"));
}

void qt_rig::timerTick()
{
	std::string sTitle=rigInfo.timerUpdate();
	setWindowTitle(sTitle.c_str());
}

void qt_rig::acceptConnection()
{
	QTcpSocket* tcpClientSocket = tcpServer.nextPendingConnection();
	
	//accept new connection
	rigInfo.acceptConnection(tcpClientSocket);

	connect(tcpClientSocket, SIGNAL(readyRead()),
		this, SLOT(clientWrite()));
	connect(tcpClientSocket, SIGNAL(disconnected()), 
		this, SLOT(clientDisconnected()));
}

void qt_rig::clientWrite()
{
	//update gui info
	QTcpSocket *client= qobject_cast<QTcpSocket *>(sender());

	if (!client)
		return;

	rigInfo.clientWrite(client);
}

void qt_rig::clientDisconnected()
{
	//client disconnected
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

	if (!client)
		return;

	rigInfo.clientDisconnected(client);

	client->deleteLater();
}