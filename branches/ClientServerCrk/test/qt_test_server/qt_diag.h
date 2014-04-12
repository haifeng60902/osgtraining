#ifndef _QT_DIAG_H_
#define _QT_DIAG_H_

#include <vector>
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
			tcpClientSocket(NULL)
		{};
		QLabel* clientLabel;
		QTcpSocket *tcpClientSocket;
		std::string sClient;
	};
	typedef std::vector<binClient> tVecClient;

	QTimer *timer;
	QVBoxLayout* diagLayout;
	QLabel* summaryLabel;

	QTcpServer tcpServer;

	tVecClient vClient;
};

#endif	//_QT_DIAG_H_