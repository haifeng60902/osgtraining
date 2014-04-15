#include <string>

#include <QtWidgets/QApplication>
#include "qt_diag.h"

std::string sHost("192.168.1.2");

int main(int argc, char *argv[])
{
	//имя конфига
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-host") == 0)
		{
			i++; if (i >= argc) break;
			sHost=QString(argv[i]).toStdString();

		}
	}
	QApplication a(argc, argv);
	qt_diag w(sHost);
	return a.exec();
}
