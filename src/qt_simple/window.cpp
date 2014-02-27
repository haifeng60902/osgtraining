#include "window.h"

window::window()
{

}

window::~window()
{

}

void window::init()
{
	mainWindow=new QWidget;
	mainWindow->setWindowTitle("Rigs Monitor");

	mainLayout=new QVBoxLayout;
	mainWindow->setLayout(mainLayout);

	addGroups();

	mainWindow->show();
}

void window::addGroups()
{

}