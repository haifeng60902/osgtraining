#ifndef _RIG_INFO_H_
#define _RIG_INFO_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

#include "binRigs.h"

class RigInfo
{
public:
	RigInfo();
	~RigInfo();

	void init(const binSetting& settings);

	//update gui info
	void update(const std::string& client, const std::string& msg);

	//get custom widget
	QWidget* getWidget();

private:
	typedef std::vector<QVBoxLayout*> tVecVBoxLayout;
	typedef std::vector<QHBoxLayout*> tVecHBoxLayout;
	typedef std::vector<QGroupBox*> tVecGroupbox;
	
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

	tVecRigLine vRigLine;

	QWidget* rigInfo;
	QVBoxLayout* rigInfoLayout;

	//for convert purpose
	tMapClient2Worker mClt2Wrk;
};

#endif	//_RIG_INFO_H_