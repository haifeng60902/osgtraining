#include <string>

#include <QtWidgets/QApplication>
#include "qt_diag.h"

int iWait=30;

int main(int argc, char *argv[])
{
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-wait") == 0)
		{
			i++; if (i >= argc) break;
			std::string sWait=QString(argv[i]).toStdString();
			iWait=atoi(sWait.c_str());

		}
	}

	QApplication a(argc, argv);
	qt_diag w(iWait);
	return a.exec();
}
