#include <string>

#include "qt_rig_server.h"
#include <QtWidgets/QApplication>

std::string sConf("workers.lua");

int main(int argc, char *argv[])
{
	//имя конфига
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-conf") == 0)
		{
			i++; if (i >= argc) break;
			sConf=argv[i];
			
			continue;
		}
	}

	QApplication a(argc, argv);
	qt_rig_server w(sConf);
	w.show();
	return a.exec();
}
