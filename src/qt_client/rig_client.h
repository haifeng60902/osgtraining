#ifndef RIG_CLIENT_H
#define RIG_CLIENT_H

#include <vector>

#include <QDialog>
#include <QSystemTrayIcon>
#include <QtNetwork>

#include "binClient.h"
#include "core/Parse/binMiner.h"
#include "saveFeedback.h"
#include "netFeedback.h"

QT_BEGIN_NAMESPACE
class QAction;
class QGroupBox;
class QLabel;
class QMenu;
class QPushButton;
class QTimer;
class QTcpSocket;
QT_END_NAMESPACE

class rig_client : public QDialog
{
	Q_OBJECT

private slots:
	void timerTick();
	void connectedClient();
	void readyReadClient();
	void hostFoundClient();
	void disconnectedClient();

	void coinSelect();
public:
	rig_client(const QString& h, const QString& r, const QString& c, QWidget *parent = 0);
	~rig_client();

protected:
	void closeEvent(QCloseEvent *event);
private:
	enum eNetMode
	{
		enTry2Connect,
		enConnectSuccess
	};

	void createTrayIcon();
	void createActions();
	void setIcon();
	void createTimer();
	void fillMap();
	void processDoNotLaunch();
	void processNetInfo(eMinerMode minerMode, const std::string& str);

	void systrayLogic();

	//save data from miner to log
	saveFeedback save;

	//send data from miner to server
	netFeedback net;

	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;

	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *quitAction;

	QIcon *iconDef;
	
	QTimer *timer;

	QTcpSocket tcpClientMiner;
	bool bOk;

	QString host;
	QString req;
	QString conf;

	std::vector<QAction*> vAction;
	std::vector<QIcon*> vIcon;

	binClient client;

	eNetMode netMode;
	eMinerMode minerMode;
	eMinerMode prevMinerMode;
	int iSwitchCoin;
	tMode2Str mode2Str;

	int iSendServ;
	int iRecvServ;
};

#endif // RIG_CLIENT_H
