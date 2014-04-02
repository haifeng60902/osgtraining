#ifndef RIG_CLIENT_H
#define RIG_CLIENT_H

#include <vector>
#include <map>

#include <QDialog>
#include <QSystemTrayIcon>
#include <QtNetwork>

#include "binClient.h"

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
	void connected();
	void readyRead();
	void hostFound();
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

	enum eMinerMode
	{
		enFirtMsg,
		enSummary,
		enPools,
		enCoin,
		enQuit
	};

	typedef std::map<eMinerMode, std::string> tMode2Str;

	void createTrayIcon();
	void createActions();
	void setIcon();
	void createTimer();
	void fillMap();

	//start miner
	void startMiner(int i);

	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;

	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *quitAction;

	QIcon *iconDef;
	
	QTimer *timer;

	QTcpSocket tcpClient;
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
};

#endif // RIG_CLIENT_H
