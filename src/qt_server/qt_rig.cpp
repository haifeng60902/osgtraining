#include "qt_rig.h"

qt_rig::qt_rig(const std::string sConf, QWidget *parent)
	: QDialog(parent)
{
	luaParseConf luaConf;
	luaConf.parse(sConf.c_str(), &settings);

	setWindowTitle("Rigs Monitor");

	mainLayout=new QVBoxLayout;
	setLayout(mainLayout);
	
	addTabs();
	//addGroups();

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

	//ui.setupUi(this);
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

	rigSett.Init(settings);
	QWidget* rigSettWidget=rigSett.GetWidget();

	tabWidget->addTab(rigInfoWidget, tr("Rigs info"));
	tabWidget->addTab(rigSettWidget, tr("Settings"));
}

void qt_rig::timerTick()
{
	static int it=0;
	++it;
}