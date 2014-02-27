#include <QApplication>
#include <QLabel>

#include "window.h"

int main(int argc, char *argv[])
{
	//get settings from lua config
	QApplication app(argc, argv);

	window win;
	win.init("rigs.lua");

	return app.exec();
}