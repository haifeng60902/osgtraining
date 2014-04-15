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
	void connectedClient();
	void readyReadClient();
	void hostFoundClient();
	void disconnectedClient();

public:
	qt_diag(QWidget *parent=NULL);
	~qt_diag();

private:

	typedef std::vector<char> tVecChar;

	//fill random string
	quint16 getRndStr(std::string* s);

	void writeMsg();

	QTimer *timer;
	QVBoxLayout* diagLayout;
	QLabel* summaryLabel;
	std::string sRead;

	QTcpSocket tcpClientServer;
	bool bConnect;
	bool bConn2Host;
};

#endif	//_QT_DIAG_H_