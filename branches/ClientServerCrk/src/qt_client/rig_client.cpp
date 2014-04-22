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
#include "winCreateProcess.h"

#include <Windows.h>

rig_client::rig_client(const QString& h, const QString& r, const QString& c, QWidget *parent)
	: host(h), req(r), conf(c), QDialog(parent), netMode(enTry2Connect), minerMode(enFirtMsg), prevMinerMode(enFirtMsg)
{
	iSwitchCoin=-1;
	luaParseConf luaConf;
	luaConf.parse(conf.toStdString().c_str(), &client);

	//set log path
	save.setLogPath(client.sLogPath);
	save.setUser(client.sUser);
	
	//net init
	net.init(client.sHostServer, client.iPortServer);

	createActions();
	createTrayIcon();
	setIcon();
	createTimer();
	fillMap();

	connect(&tcpClientMiner, SIGNAL(connected()),this, SLOT(connectedClient()));
	connect(&tcpClientMiner, SIGNAL(readyRead()),this, SLOT(readyReadClient()));
	connect(&tcpClientMiner, SIGNAL(hostFound()),this, SLOT(hostFoundClient()));
	connect(&tcpClientMiner, SIGNAL(disconnected()),this, SLOT(disconnectedClient()));

	if(client.bShowSysTray)
		trayIcon->show();
	else
		trayIcon->hide();

	iSendServ=0;
	iRecvServ=0;
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

	//switch to J coin
	iSwitchCoin=j;
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
	systrayLogic();

	bool bServer=net.process();

	std::string sTip="Server:";
	if (bServer)
		sTip+="Yes|";
	else
		sTip+="No|";

	if (netMode==enTry2Connect)
	{
		sTip+="Client:No";
		minerMode=enFirtMsg;
	}
	else
		sTip+="Client:Yes";

	trayIcon->setToolTip(sTip.c_str());

	netMode=enTry2Connect;
	tcpClientMiner.connectToHost(client.sHostMiner.c_str(), client.iPortMiner, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
}

void rig_client::processDoNotLaunch()
{
	vAction[iSwitchCoin]->setEnabled(true);
	vAction[iSwitchCoin]->setChecked(false);
	trayIcon->setIcon(*iconDef);
	setWindowIcon(*iconDef);
}

void rig_client::connectedClient()
{
	if (minerMode==enFirtMsg)
		minerMode=(eMinerMode)((int)minerMode+1);
	
	//minerMode=enSummary;
	std::string sReq=mode2Str[minerMode];
	tcpClientMiner.write(sReq.c_str());
}

void rig_client::readyReadClient()
{
	QString sR= tcpClientMiner.readAll();
	
	setWindowTitle(sR);
	tcpClientMiner.disconnectFromHost();

	processNetInfo(minerMode, sR.toStdString());

	if (minerMode==enQuit)
		minerMode=enFirtMsg;
	else
	{
		minerMode=(eMinerMode)((int)minerMode+1);
		if(minerMode==enQuit)
			minerMode=enSummary;
	}	
}

void rig_client::processNetInfo(eMinerMode mode, const std::string& str)
{
	//save string to log
	save.parse(mode, str);

	//store message for late processing
	net.push_msg(str);
}

void rig_client::hostFoundClient()
{
	netMode=enConnectSuccess;
}

void rig_client::disconnectedClient()
{

}

void rig_client::fillMap()
{
	mode2Str[enFirtMsg]="error";
	mode2Str[enSummary]="summary";
	mode2Str[enPools]="pools";
//	mode2Str[enCoin]="coin";
	mode2Str[enDevs]="devs";
	mode2Str[enQuit]="quit";
}

void rig_client::systrayLogic()
{
	if (iSwitchCoin>-1)
	{
		if (minerMode==enFirtMsg)
		{
			//start miner
			winCreateProcess win;
			bool bRes=win.create(iSwitchCoin, client);
			if (!bRes)
				processDoNotLaunch();

			iSwitchCoin=-1;

			return;
		}
		else
		{
			minerMode=enQuit;
		}
	}
}