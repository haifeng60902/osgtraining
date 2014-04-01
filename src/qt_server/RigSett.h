#ifndef _RIG_SETT_H_
#define _RIG_SETT_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

#include "binRigs.h"

class RigSett:public QWidget
{
	 Q_OBJECT
public:
	RigSett();
	~RigSett();

	void Init(const binSetting& settings);

	//get custom widget
	QWidget* GetWidget();

private slots:
		void okClicked(); 
		void setIcon(int index);

private:

	void addSelectGroup(const binSetting& settings);
	void addInfoGroup(const binSetting& settings);

	void updateInfoLabel(int i, const binSetting& settings);

	//QWidget* rigSett;
	QVBoxLayout* rigSettLayout;
	QGroupBox* groupCombo;
	QVBoxLayout* comboLayout;
	QGroupBox* groupInfo;
	QVBoxLayout* infoLayout;
	QComboBox *iconComboBox;
	QLabel *coinLabel;
	QLabel *minerLabel;
	QLabel *poolsLabel;

	QPushButton *okButton;

	//local copy of settings
	binSetting sett;
};

#endif	//_RIG_SETT_H_