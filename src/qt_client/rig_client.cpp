#include "rig_client.h"

#include <QAction>
#include <QGroupBox>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QTimer>

#include "luaParseConf.h"

rig_client::rig_client(const QString& h, const QString& r, const QString& c, QWidget *parent)
	: host(h), req(r), conf(c), QDialog(parent)
{
	luaParseConf luaConf;
	luaConf.parse(conf.toStdString().c_str(), &client);

	createActions();
	createTrayIcon();
	setIcon();
	createTimer();

	connect(&tcpClient, SIGNAL(connected()),this, SLOT(connected()));
	connect(&tcpClient, SIGNAL(readyRead()),this, SLOT(readyRead()));
	connect(&tcpClient, SIGNAL(hostFound()),this, SLOT(hostFound()));

	trayIcon->show();
	//trayIcon->hide();
	bOk=true;
	//ui.setupUi(this);
}

rig_client::~rig_client()
{

}

void rig_client::createActions()
{
	for(int i=0;i<client.vCoins.size();++i)
	{
		QIcon* icon=new QIcon(client.vCoins[i].sIcon.c_str());
		vIcon.push_back(icon);

		QAction* action=new QAction(*icon, client.vCoins[i].sCoin.c_str(), this);
		action->setCheckable(true);
		
		vAction.push_back(action);
		connect(action, SIGNAL(triggered()), this, SLOT(coinSelect()));
	}

	minimizeAction = new QAction(tr("Mi&nimize"), this);
	connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

	restoreAction = new QAction(tr("&Restore"), this);
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

	quitAction = new QAction(tr("&Quit"), this);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void rig_client::coinSelect()
{
	int j=0;
	for(int i=0;i<vAction.size();++i)
	{
		bool b1=vAction[i]->isEnabled();
		bool b2=vAction[i]->isChecked();
		if ((b2)&&(b1))
		{
			j=i;
			vAction[i]->setEnabled(false);
			trayIcon->setIcon(*vIcon[i]);
			setWindowIcon(*vIcon[i]);
			break;
		}
	}
	for(int i=0;i<vAction.size();++i)
	{
		if (i!=j)
		{
			vAction[i]->setEnabled(true);
			vAction[i]->setChecked(false);
		}
	}
}

void rig_client::createTrayIcon()
{


	trayIconMenu = new QMenu(this);
	for(int i=0;i<vAction.size();++i)
		trayIconMenu->addAction(vAction[i]);

	trayIconMenu->addSeparator();
	trayIconMenu->addAction(minimizeAction);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
}

void rig_client::setIcon()
{
	iconDef = new QIcon("icons/money.png");
	trayIcon->setIcon(*iconDef);
	setWindowIcon(*iconDef);
	trayIcon->setToolTip(tr("0"));
}

void rig_client::closeEvent(QCloseEvent *event)
{
	if (trayIcon->isVisible())
	{
		hide();
		event->ignore();
	}
}

void rig_client::createTimer()
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
	timer->start(1000);
}

void rig_client::timerTick()
{
	static int i=0;
	setWindowTitle(QString::number(i));
	trayIcon->setToolTip(QString::number(i));
	
	++i;

	if (bOk)
	{
		tcpClient.connectToHost(host, 4028, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
		bOk=false;
	}
	else
		setWindowTitle("ERROR timerTick");
}

void rig_client::connected()
{
	tcpClient.write(req.toStdString().c_str());
}

void rig_client::readyRead()
{
	QString sR= tcpClient.readAll();
	setWindowTitle(sR);
	tcpClient.disconnectFromHost();
	bOk=true;
}

void rig_client::hostFound()
{
	int a=1;
}