#include "qt_rig_server.h"

#include <QMessageBox>

qt_rig_server::qt_rig_server(const std::string sConf, QWidget *parent)
	: QDialog(parent)
{
	luaParseConfServer luaConf;
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

qt_rig_server::~qt_rig_server()
{

}

void qt_rig_server::addTabs()
{
	tabWidget = new QTabWidget(this);

	mainLayout->addWidget(tabWidget);
}

void qt_rig_server::timerTick()
{
	setWindowTitle("tick");
}

void qt_rig_server::acceptConnection()
{
	QTcpSocket* tcpClientSocket = tcpServer.nextPendingConnection();

	connect(tcpClientSocket, SIGNAL(readyRead()),
		this, SLOT(clientWrite()));
	connect(tcpClientSocket, SIGNAL(disconnected()), 
		this, SLOT(clientDisconnected()));
}

void qt_rig_server::clientWrite()
{
	//update gui info
	QTcpSocket *client= qobject_cast<QTcpSocket *>(sender());

	if (!client)
		return;
}

void qt_rig_server::clientDisconnected()
{
	//client disconnected
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

	if (!client)
		return;
}