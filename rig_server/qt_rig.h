#ifndef QT_RIG_H
#define QT_RIG_H

#include <QtWidgets/QDialog>
#include <vector>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTimer>

#include "ui_qt_rig.h"
#include "luaParseConf.h"

class qt_rig : public QDialog
{
	Q_OBJECT

public:
	qt_rig(QWidget *parent = 0);
	~qt_rig();

private slots:
	void timerTick();

private:
	typedef std::vector<QVBoxLayout*> tVecVBoxLayout;
	typedef std::vector<QHBoxLayout*> tVecHBoxLayout;
	typedef std::vector<QGroupBox*> tVecGroupbox;

	struct  binRigLine
	{
		QHBoxLayout* lineLayout;			//one line in vertical grid
		tVecGroupbox vGroupBox;					//line of group boxs 
		tVecVBoxLayout vLayoutInGroupBox;	//a vertical layout for one group box
	};
	typedef std::vector<binRigLine> tVecRigLine;

	void addGroups();

	QWidget *mainWindow;
	QVBoxLayout* mainLayout;
	tVecRigLine vRigLine;

	QTimer *timer;

	Ui::qt_rigClass ui;

	//settings from lua config
	binSetting settins;
};

#endif // QT_RIG_H
