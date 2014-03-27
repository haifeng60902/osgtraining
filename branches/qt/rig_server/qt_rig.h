#ifndef QT_RIG_H
#define QT_RIG_H

#include <QtWidgets/QDialog>
#include <vector>

#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTimer>

#include "ui_qt_rig.h"
#include "luaParseConf.h"
#include "RigInfo.h"

class qt_rig : public QDialog
{
	Q_OBJECT

public:
	qt_rig(QWidget *parent = 0);
	~qt_rig();

private slots:
	void timerTick();

private:
	void addTabs();

	QTabWidget *tabWidget;
	QWidget* tab2;
	QHBoxLayout* tab2Layout;

	QWidget *mainWindow;
	QVBoxLayout* mainLayout;
	
	QTimer *timer;

	Ui::qt_rigClass ui;

	//rig info tab
	RigInfo rigInfo;

	//settings from lua config
	binSetting settings;
};

#endif // QT_RIG_H
