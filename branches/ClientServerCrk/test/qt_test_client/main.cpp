#include <string>

#include <QtWidgets/QApplication>
#include "qt_diag.h"

#include "test_hlp.h"

std::string sHost("192.168.1.2");
int iTick=3000;

int main(int argc, char *argv[])
{
	//test_hlp hlp;
	//hlp.check();

	//имя конфига
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-host") == 0)
		{
			i++; if (i >= argc) break;
			sHost=QString(argv[i]).toStdString();

		}
		else if (strcmp(argv[i], "-tick") == 0)
		{
			i++; if (i >= argc) break;
			std::string sTick=QString(argv[i]).toStdString();
			iTick=atoi(sTick.c_str());

		}
	}
	QApplication a(argc, argv);
	qt_diag w(sHost,iTick);
	return a.exec();
}
