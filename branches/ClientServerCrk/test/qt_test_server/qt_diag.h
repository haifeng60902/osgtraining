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
	void acceptConnection();
	void updateServer();
	void clientDisconnected();

public:
	qt_diag(QWidget *parent=NULL);
	~qt_diag();

private:
	struct binClient
	{
		binClient():clientLabel(NULL),
			iMsgSize(0),
			iMsgClue(0),
			iMsgRead(0)
		{};
		QLabel* clientLabel;
		std::string sClient;
		int iMsgSize;
		int iMsgRead;
		int iMsgClue;
	};
	typedef std::map<QTcpSocket*, binClient> tMapClient;

	//fill string random char
	void getRandStr(std::string* s);

	QTimer *timer;
	QVBoxLayout* diagLayout;
	QLabel* summaryLabel;

	QTcpServer tcpServer;

	tMapClient mClient;
};

#endif	//_QT_DIAG_H_