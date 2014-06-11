#ifndef QT_RIG_H
#define QT_RIG_H

#include <vector>
#include <string>

#include <QtWidgets/QDialog>

#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTimer>

#include <QTcpServer>
#include <QTcpSocket>

#include "binRigs.h"
#include "luaParseConfServer.h"

class qt_rig_server : public QDialog
{
	Q_OBJECT

public:
	qt_rig_server(const std::string sConf, QWidget *parent = 0);
	~qt_rig_server();

	private slots:
		void timerTick();
		void acceptConnection();
		void clientWrite();
		void clientDisconnected();

private:
	void addTabs();

	QTabWidget *tabWidget;
	QWidget* tab2;
	QHBoxLayout* tab2Layout;

	QWidget *mainWindow;
	QVBoxLayout* mainLayout;

	QTimer *timer;

	//settings from lua config
	binSetting settings;

	QTcpServer tcpServer;
};

#endif // QT_RIG_H
