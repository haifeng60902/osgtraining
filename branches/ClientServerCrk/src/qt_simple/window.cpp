#include "window.h"

#include "luaParseConf.h"

window::window()
{

}

window::~window()
{

}

void window::init(const char* conf)
{
	luaParseConf luaConf;
	luaConf.parse(conf, &settins);

	mainWindow=new QWidget;
	mainWindow->setWindowTitle("Rigs Monitor");

	mainLayout=new QVBoxLayout;
	mainWindow->setLayout(mainLayout);

	addGroups();

	mainWindow->show();

	timer=new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start();
}

void window::update()
{
	QWidget::update();
	static int a=0;
	a;
}

void window::addGroups()
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
	int a=1;
}