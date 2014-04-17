#ifndef _RIG_INFO_H_
#define _RIG_INFO_H_

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

class RigInfo
{
public:
	RigInfo();
	~RigInfo();

	void init(const binSetting& settings);

	//accept new connection
	void acceptConnection(QTcpSocket* tcpClientSocket);

	//read message from client
	void clientWrite(QTcpSocket* tcpClientSocket);

	//client disconnected
	void clientDisconnected(QTcpSocket* tcpClientSocket);

	//detect disconnect workers
	void timerUpdate();

	//get custom widget
	QWidget* getWidget();

private:
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
			iWait(DISCONNECT_WAIT)
		{};
		std::string sClient;
		int iMsgSize;
		int iMsgRead;
		int iMsgClue;
		int iWait;
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

	void processPools(eMinerMode mode, const std::string& client, const std::string& msg);
	void processSummary(eMinerMode mode, const std::string& client, const std::string& msg);
	void processCoin(eMinerMode mode, const std::string& client, const std::string& msg);
	void processDevs(eMinerMode mode, const std::string& client, const std::string& msg);

	//update gui info
	void update(const std::string& client, const std::string& msg);

	//fill main info
	void fillPoolInfo(binInfo* info, const binPools& ps, const std::string& msg);

	tVecRigLine vRigLine;

	QWidget* rigInfo;
	QVBoxLayout* rigInfoLayout;

	//worker info
	tMapInfo mInfo;

	//active clients
	tMapClient mClient;

	int iWAIT;
};

#endif	//_RIG_INFO_H_