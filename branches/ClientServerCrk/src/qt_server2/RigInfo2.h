#ifndef _RIG_INFO_2_H_
#define _RIG_INFO_2_H_

#include <vector>
#include <map>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTcpSocket>

#include "core/Parse/binMiner.h"
#include "binRigs.h"

class RigInfo2
{
public:
	RigInfo2();
	~RigInfo2();

	void init(const binSetting& settings);

	//get main widget
	QWidget* getWidget();

	//accept new connection
	void acceptConnection(QTcpSocket* tcpClientSocket);

	//read message from client
	void clientWrite(QTcpSocket* tcpClientSocket);

	//client disconnected
	void clientDisconnected(QTcpSocket* tcpClientSocket);

	//detect disconnect workers
	std::string timerUpdate();

protected:
	typedef std::vector<QVBoxLayout*> tVecVBoxLayout;
	typedef std::vector<QHBoxLayout*> tVecHBoxLayout;
	typedef std::vector<QGroupBox*> tVecGroupbox;
	typedef std::vector<QLabel*> tVecLabel;

	struct binInfo
	{
		binInfo():iTick(DISCONNECT_WAIT),
			lBox(NULL)
		{};
		int iTick;
		QGroupBox* gBox;
		QVBoxLayout* lBox;
		tVecLabel vLabel;
	};
	//key-worker
	typedef std::map<std::string, binInfo> tMapInfo;

	struct binClient
	{
		binClient():iMsgSize(0),
			iMsgClue(0),
			iMsgRead(0),
			iWait(DISCONNECT_WAIT),
			iHash(0)
		{};
		std::string sClient;
		int iMsgSize;
		int iMsgRead;
		int iMsgClue;
		int iWait;
		int iHash;
	};
	typedef std::map<QTcpSocket*, binClient> tMapClient;

	struct  binRigLine
	{
		QHBoxLayout* lineLayout;			//one line in vertical grid
		tVecGroupbox vGroupBox;					//line of group boxs 
		tVecVBoxLayout vLayoutInGroupBox;	//a vertical layout for one group box
	};
	typedef std::vector<binRigLine> tVecRigLine;

	void addGroups(const binSetting& settings);

	//update gui info
	void updateGui(const std::string& client, const std::string& msg, int* hash);

	void processSummary(eMinerMode mode, const std::string& client, const std::string& msg, int* hash);

	QWidget* rigInfo;	//main widget
	QVBoxLayout* rigInfoLayout;//main layout in widget

	//worker info
	tMapInfo mInfo;

	//active clients
	tMapClient mClient;
	
	//lines vector
	tVecRigLine vRigLine;

	//global client wait time
	int iWAIT;
};

#endif	//_RIG_INFO_2_H_