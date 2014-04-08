#include "saveFeedback.h"
#include "core/Parse/parse.h"

#include <Windows.h>

saveFeedback::saveFeedback()
{

}

saveFeedback::~saveFeedback()
{

}

void saveFeedback::parse(eMinerMode mode, const std::string& msg)
{
	//save string to log
	switch (mode)
	{
	case enSummary:
		saveSummary(msg);
		break;
		/*
	case enPools:
		decodePools(msg);
		break;
	case enCoin:
		decodeCoin(msg);
		break;
	case enDevs:
		decodeDevs(msg);
		break;
		*/
	default:
		break;
	}
}

void saveFeedback::saveSummary(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	Parse::Substr(msg, &vStr);

	if (vStr.size()>1)
	{
		binSummary s;
		s.tTime=Parse::GetInt(vStr[0],"When=");
		
		struct tm * timeinfo;
		timeinfo = localtime(&s.tTime);
		
	}
}

bool saveFeedback::directoryExists(const char* dirName)
{
	//check directory exist
	DWORD attribs = ::GetFileAttributesA(dirName);
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}