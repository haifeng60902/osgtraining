#ifndef _QT_DIAG_H_
#define _QT_DIAG_H_

#include <map>
#include <string>

#include <QDialog>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QTcpServer>
#include <QTcpSocket>

class qt_diag: public QDialog
{
	Q_OBJECT

private slots:
	void timerTick();

public:
	qt_diag(QWidget *parent=NULL);
	~qt_diag();

private:

	//fill string random char
	void getRandStr(std::string* s);

	QTimer *timer;
	QVBoxLayout* diagLayout;
	QLabel* summaryLabel;
};

#endif	//_QT_DIAG_H_