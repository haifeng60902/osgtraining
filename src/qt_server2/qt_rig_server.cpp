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

	rigInfo2.init(settings);
	QWidget* rigInfoWidget=rigInfo2.getWidget();

	tabWidget->addTab(rigInfoWidget, tr("Rigs info"));
}

void qt_rig_server::timerTick()
{
	std::string sTitle=rigInfo2.timerUpdate();
	setWindowTitle(sTitle.c_str());
}

void qt_rig_server::acceptConnection()
{
	QTcpSocket* tcpClientSocket = tcpServer.nextPendingConnection();

	//accept new connection
	rigInfo2.acceptConnection(tcpClientSocket);

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

	rigInfo2.clientWrite(client);
}

void qt_rig_server::clientDisconnected()
{
	//client disconnected
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

	if (!client)
		return;

	rigInfo2.clientDisconnected(client);

	client->deleteLater();
}