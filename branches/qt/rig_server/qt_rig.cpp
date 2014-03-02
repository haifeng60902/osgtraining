#include "qt_rig.h"

qt_rig::qt_rig(QWidget *parent)
	: QDialog(parent)
{
	luaParseConf luaConf;
	luaConf.parse("rigs.lua", &settins);

	setWindowTitle("Rigs Monitor");

	mainLayout=new QVBoxLayout;
	setLayout(mainLayout);

	addGroups();

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

	ui.setupUi(this);
}

qt_rig::~qt_rig()
{

}

void qt_rig::addGroups()
{
	int row=settins.vRigs.size()/settins.iColumn;
	int last=settins.vRigs.size()%settins.iColumn;
	if (last>0)
		++row;

	int k=0;
	for (int i=0;i<row;++i)
	{
		binRigLine line;
		line.lineLayout=new QHBoxLayout;
		mainLayout->addLayout(line.lineLayout);
		for (int j=0;j<settins.iColumn;++j)
		{
			QGroupBox* box=new QGroupBox;
			QVBoxLayout* layoutBox=new QVBoxLayout;
			box->setTitle(settins.vRigs[k].sRig.c_str());
			box->setLayout(layoutBox);

			line.vGroupBox.push_back(box);
			line.vLayoutInGroupBox.push_back(layoutBox);

			line.lineLayout->addWidget(box);

			++k;

			if (k==settins.vRigs.size())
				break;
		}
		vRigLine.push_back(line);
	}
}

void qt_rig::timerTick()
{
	static int it=0;
	++it;
}