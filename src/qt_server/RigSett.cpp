#include "RigSett.h"

RigSett::RigSett()
{

}

RigSett::~RigSett()
{

}

void RigSett::Init(const binSetting& settings)
{
	sett=settings;
	rigSettLayout=new QVBoxLayout;
	this->setLayout(rigSettLayout);

	addSelectGroup(settings);
	addInfoGroup(settings);

	connect(okButton, SIGNAL(clicked()),
		this, SLOT(okClicked())); 
}

//get custom widget
QWidget* RigSett::GetWidget()
{
	return this;
}

void RigSett::addSelectGroup(const binSetting& settings)
{
	groupCombo=new QGroupBox;
	groupCombo->setTitle("Coin choice");
	comboLayout=new QVBoxLayout;
	groupCombo->setLayout(comboLayout);

	iconComboBox = new QComboBox;

	for(int i=0;i<settings.vModes.size();++i)
		iconComboBox->addItem(QIcon(settings.vModes[i].sIcon.c_str()), settings.vModes[i].sCoin.c_str());

	comboLayout->addWidget(iconComboBox);

	okButton = new QPushButton("&OK");
	okButton->setDefault(true);
	okButton->setEnabled(true);
	comboLayout->addWidget(okButton);

	rigSettLayout->addWidget(groupCombo);

	connect(iconComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setIcon(int)));
}

void RigSett::addInfoGroup(const binSetting& settings)
{
	groupInfo=new QGroupBox;
	groupInfo->setTitle("Coin info");
	infoLayout=new QVBoxLayout;
	groupInfo->setLayout(infoLayout);

	coinLabel=new QLabel;
	minerLabel=new QLabel;
	poolsLabel=new QLabel;

	updateInfoLabel(0, settings);

	infoLayout->addWidget(coinLabel);
	infoLayout->addWidget(minerLabel);
	infoLayout->addWidget(poolsLabel);

	rigSettLayout->addWidget(groupInfo);
}

void RigSett::updateInfoLabel(int i, const binSetting& settings)
{
	std::string sCoin("Coin: ");
	std::string sMiner("Miner: ");
	std::string sPools("Pools: ");

	if (!settings.vModes.empty())
	{
		sCoin+=settings.vModes[i].sCoin;
		sMiner+=settings.vModes[i].sMiner;
		for(int j=0;j<settings.vModes[i].vPools.size();++j)
		{
			if (j>0)
				sPools+=" , ";
			sPools+=settings.vModes[i].vPools[j];
		}
	}

	coinLabel->setText(sCoin.c_str());
	minerLabel->setText(sMiner.c_str());
	poolsLabel->setText(sPools.c_str());
}

void RigSett::okClicked()
{
	int a=1;
}

void RigSett::setIcon(int index)
{
	updateInfoLabel(index, sett);
}
