#include "qt_rig.h"

qt_rig::qt_rig(QWidget *parent)
	: QDialog(parent)
{
	luaParseConf luaConf;
	luaConf.parse("rigs.lua", &settings);

	setWindowTitle("Rigs Monitor");

	mainLayout=new QVBoxLayout;
	setLayout(mainLayout);
	
	addTabs();
	//addGroups();

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

	ui.setupUi(this);
}

qt_rig::~qt_rig()
{

}

void qt_rig::addTabs()
{
	tabWidget = new QTabWidget(this);

	mainLayout->addWidget(tabWidget);

	rigInfo.Init(settings);
	QWidget* rigInfoWidget=rigInfo.GetWidget();

	tab2=new QWidget;
	tabWidget->addTab(rigInfoWidget, tr("Rigs info"));
	tabWidget->addTab(tab2,tr("Settings"));
	
	tab2Layout=new QHBoxLayout;
	tab2->setLayout(tab2Layout);	
}

void qt_rig::timerTick()
{
	static int it=0;
	++it;
}