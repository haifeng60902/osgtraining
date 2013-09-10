#include <iostream>

#include <string>
#include "binInput.h"
#include "FirstPass.h"

binInput in;

int main(int argc, char** argv)
{
	//парсинг входной строки
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-exe") == 0)
		{
			i++; if (i >= argc) break;
			in.exeFile = argv[i];
			continue;
		}
		if (strcmp(argv[i], "-hash") == 0)
		{
			i++; if (i >= argc) break;
			in.hashFile = argv[i];
			continue;
		}
		if (strcmp(argv[i], "-time") == 0)
		{
			i++; if (i >= argc) break;
			in.runTime = atof(argv[i]);
			continue;
		}
	}

	FirstPass fp;
	fp.Init(in);
	fp.Save();
}