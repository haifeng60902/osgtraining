#include "qt_rig.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt_rig w;
	w.show();
	return a.exec();
}
