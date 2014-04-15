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

#include "luaParseConf.h"
#include "RigInfo.h"
#include "RigSett.h"

class qt_rig : public QDialog
{
	Q_OBJECT

public:
	qt_rig(const std::string sConf, QWidget *parent = 0);
	~qt_rig();

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

	//Ui::qt_rigClass ui;

	//rig info tab
	RigInfo rigInfo;

	//rig settings tab
	RigSett rigSett;

	//settings from lua config
	binSetting settings;

	QTcpServer tcpServer;
};

#endif // QT_RIG_H
