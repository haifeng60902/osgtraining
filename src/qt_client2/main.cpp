#include "rig_client.h"
#include <QApplication>
#include <ctime>
#include <string>

QString host="localhost";
QString req="config";
QString conf="local.lua";

int main(int argc, char *argv[])
{
	//имя конфига
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-host") == 0)
		{
			i++; if (i >= argc) break;
			host=QString(argv[i]);
			continue;
		}
		if (strcmp(argv[i], "-req") == 0)
		{
			i++; if (i >= argc) break;
			req=QString(argv[i]);
			continue;
		}
		if (strcmp(argv[i], "-conf") == 0)
		{
			i++; if (i >= argc) break;
			conf=QString(argv[i]);
			continue;
		}
	}

	QApplication a(argc, argv);
	rig_client w(host,req,conf);
	return a.exec();
}
