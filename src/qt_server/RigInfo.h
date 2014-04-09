#ifndef _RIG_INFO_H_
#define _RIG_INFO_H_

#include <vector>
#include <map>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>

#include "core/Parse/binMiner.h"
#include "binRigs.h"

class RigInfo
{
public:
	RigInfo();
	~RigInfo();

	void init(const binSetting& settings);

	//update gui info
	void update(const std::string& client, const std::string& msg);

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
		QVBoxLayout* lBox;
		tVecLabel vLabel;
	};
	//key-worker
	typedef std::map<std::string, binInfo> tMapInfo;
	
	//key-client network address, value-worker name
	typedef std::map<std::string, std::string> tMapClient2Worker;

	struct  binRigLine
	{
		QHBoxLayout* lineLayout;			//one line in vertical grid
		tVecGroupbox vGroupBox;					//line of group boxs 
		tVecVBoxLayout vLayoutInGroupBox;	//a vertical layout for one group box
	};
	typedef std::vector<binRigLine> tVecRigLine;

	void addGroups(const binSetting& settings);

	void processPools(eMinerMode mode, const std::string& client, const std::string& msg);

	//fill main info
	void fillPoolInfo(binInfo* info, const binPools& ps, const std::string& msg);

	tVecRigLine vRigLine;

	QWidget* rigInfo;
	QVBoxLayout* rigInfoLayout;

	//for convert purpose
	tMapClient2Worker mClt2Wrk;

	//worker info
	tMapInfo mInfo;
};

#endif	//_RIG_INFO_H_