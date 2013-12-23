#include <iostream>

#include "binHosts.h"
#include "HostsCfg.h"
#include "BatGen.h"
#include "BatStart.h"

int main(int argc, char **argv)
{
	std::string sPool;
	std::string sCfg;
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-net") == 0)
		{
			i++; if (i >= argc) break;
			sCfg=argv[i];
			continue;
		}
		else if (strcmp(argv[i], "-pool") == 0)
		{
			i++; if (i >= argc) break;
			sPool=argv[i];
			continue;
		}
	}

	HostsCfg cfg;
	if(!cfg.Load(sCfg.c_str()))
		return -1;

	std::cout<<"Bat file generation pass:\n";
	BatGen batGen;
	tVecHosts &vHosts=cfg.GetHosts();
	for (int i=0;i<vHosts.size();++i)
	{
		std::cout<<"  "<<vHosts[i].sHost<<"...";
		vHosts[i].bBat=batGen.Gen(vHosts[i], sPool);
		if (vHosts[i].bBat)
			std::cout<<"OK\n";
		else
			std::cout<<"FAILED\n";
	}

	std::cout<<"Bat file start pass:\n";
	BatStart batStart;
	batStart.Process(vHosts);
}