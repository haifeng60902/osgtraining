#include "RigInfo.h"

RigInfo::RigInfo()
{

}

RigInfo::~RigInfo()
{

}

void RigInfo::init(const binSetting& settings)
{
	rigInfo=new QWidget;
	rigInfoLayout=new QVBoxLayout;
	rigInfo->setLayout(rigInfoLayout);

	addGroups(settings);
}

void RigInfo::addGroups(const binSetting& settings)
{
	int row=settings.vRigs.size()/settings.iColumn;
	int last=settings.vRigs.size()%settings.iColumn;
	if (last>0)
		++row;

	int k=0;
	for (int i=0;i<row;++i)
	{
		binRigLine line;
		line.lineLayout=new QHBoxLayout;
		rigInfoLayout->addLayout(line.lineLayout);
		for (int j=0;j<settings.iColumn;++j)
		{
			QGroupBox* box=new QGroupBox;
			QVBoxLayout* layoutBox=new QVBoxLayout;
			box->setTitle(settings.vRigs[k].sRig.c_str());
			box->setLayout(layoutBox);

			line.vGroupBox.push_back(box);
			line.vLayoutInGroupBox.push_back(layoutBox);

			line.lineLayout->addWidget(box);

			++k;

			if (k==settings.vRigs.size())
				break;
		}
		vRigLine.push_back(line);
	}
}

//get custom widget
QWidget* RigInfo::getWidget()
{
	return rigInfo;
}

void RigInfo::update(const std::string& client, const std::string& msg)
{
	//update gui info

}