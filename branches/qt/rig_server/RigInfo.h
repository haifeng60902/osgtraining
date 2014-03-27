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

	void Init(const binSetting& settings);

	//get custom widget
	QWidget* GetWidget();

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

	void addGroups(const binSetting& settings);

	tVecRigLine vRigLine;

	QWidget* rigInfo;
	QVBoxLayout* rigInfoLayout;
};

#endif	//_RIG_INFO_H_