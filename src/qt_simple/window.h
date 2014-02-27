#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <vector>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

class window
{
public:
	window();
	~window();

	void init();

	void show();

private:
	typedef std::vector<QVBoxLayout*> tVecVBoxLayout;
	typedef std::vector<QHBoxLayout*> tVecHBoxLayout;
	typedef std::vector<QGroupBox*> tVecGroupbox;

	struct  binRigLine
	{
		QHBoxLayout* lineLayout;			//one line in vertical grid
		tVecGroupbox vRigs;					//line of group boxs 
		tVecVBoxLayout vGroupInfoLayout;	//a vertical layout for one group box
	};
	typedef std::vector<binRigLine> tVecRigLine;
	
	void addGroups();

	QWidget *mainWindow;
	QVBoxLayout* mainLayout;
	tVecRigLine vRigLine;
};

#endif	//_WINDOW_H_