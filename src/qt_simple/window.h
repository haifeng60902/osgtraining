#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <vector>

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTimer>
#include <QtGui>

#include "binRigs.h"
#include "luaParseConf.h"

class window: public QDialog
{
	Q_OBJECT
public:
	window();
	~window();

	void init(const char* conf);

	void show();

signals:
	void findNext(const QString &str, Qt::CaseSensitivity cs);
	void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
	void findClicked();
	void enableFindButton(const QString &text);

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

	//settings from lua config
	binSetting settins;

	int m_timerId;

	QTimer *timer;

private slots:
		void update();

};

#endif	//_WINDOW_H_