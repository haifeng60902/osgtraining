#include "qt_diag.h"

qt_diag::qt_diag(QWidget *parent):QDialog(parent)
{
	diagLayout=new QVBoxLayout;
	setLayout(diagLayout);
	setVisible(true);

	summaryLabel=new QLabel;
	diagLayout->addWidget(summaryLabel);

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
}

qt_diag::~qt_diag()
{

}

void qt_diag::timerTick()
{
	static int i=0;
	summaryLabel->setText(std::to_string(i).c_str());
	++i;
}