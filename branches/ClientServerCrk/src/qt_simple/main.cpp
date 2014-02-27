#include <QApplication>
#include <QLabel>

#include "window.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	window win;
	win.init();
	//QLabel *label = new QLabel("Hello Qt!");
	//label->show();
	return app.exec();
}