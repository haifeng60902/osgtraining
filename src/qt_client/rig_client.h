#ifndef RIG_CLIENT_H
#define RIG_CLIENT_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QtNetwork>
//#include "ui_rig_client.h"

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
public:
	rig_client(const QString& h, const QString& r, const QString& c, QWidget *parent = 0);
	~rig_client();

protected:
	void closeEvent(QCloseEvent *event);
private:
	void createTrayIcon();
	void createActions();
	void setIcon();
	void createTimer();

	//Ui::rig_clientClass ui;
	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;

	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *quitAction;

	QIcon *iconBad;
	QIcon *iconHeart;
	QIcon *iconTrash;

	QTimer *timer;

	QTcpSocket tcpClient;
	bool bOk;

	QString host;
	QString req;
	QString conf;
};

#endif // RIG_CLIENT_H
