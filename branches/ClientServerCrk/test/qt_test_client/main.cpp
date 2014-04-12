#include <string>

#include <QtWidgets/QApplication>
#include "qt_diag.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt_diag w;
	return a.exec();
}
