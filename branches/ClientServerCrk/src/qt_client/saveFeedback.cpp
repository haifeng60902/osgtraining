#include "saveFeedback.h"

#include <fstream>
#include <Windows.h>

#include "core/Parse/parse.h"

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
		saveMsg(msg,"summary");
		break;
	case enPools:
		saveMsg(msg, "pools");
		break;
	case enCoin:
		saveMsg(msg, "coin");
		break;
	case enDevs:
		saveMsg(msg, "devs");
		break;
	default:
		break;
	}
}

void saveFeedback::saveMsg(const std::string& msg, const std::string& mode)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	Parse::Substr(msg, &vStr);

	if (vStr.size()>1)
	{
		binSummary s;
		s.tTime=Parse::GetInt(vStr[0],"When=");
		
		tm * timeinfo=NULL;
		timeinfo = localtime(&s.tTime);
		
		std::string sDir=createDir(timeinfo,mode);
		if (!sDir.empty())
			//append string to file
			append2File(sDir, msg, timeinfo->tm_hour);
	}
}

//create dir
std::string saveFeedback::createDir(const tm* timeinfo, const std::string& mode)
{
	bool bRes=false;
	std::string sFullPath;

	if (CreateDirectory(sLogPath.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		std::string sPath=sLogPath+sUser;
		if (CreateDirectory(sPath.c_str(), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			std::string sYear=std::to_string(timeinfo->tm_year+1900);
			sPath=sPath+"/"+sYear;
			if (CreateDirectory(sPath.c_str(), NULL) ||
				ERROR_ALREADY_EXISTS == GetLastError())
			{
				std::string sMon=std::to_string(timeinfo->tm_mon);
				sPath=sPath+"/"+sMon;
				if (CreateDirectory(sPath.c_str(), NULL) ||
					ERROR_ALREADY_EXISTS == GetLastError())
				{
					std::string sDay=std::to_string(timeinfo->tm_mday);
					sPath=sPath+"/"+sDay;
					if (CreateDirectory(sPath.c_str(), NULL) ||
						ERROR_ALREADY_EXISTS == GetLastError())
					{
						sPath=sPath+"/"+mode;
						if (CreateDirectory(sPath.c_str(), NULL) ||
							ERROR_ALREADY_EXISTS == GetLastError())
						{
							bRes=true;
							sFullPath=sPath;
						}
					}
				}
			}
		}
	}
	
	return sFullPath;
}

void saveFeedback::append2File(const std::string& path, const std::string& msg, int hour)
{
	//append string to file
	std::string sFile=path+"/"+std::to_string(hour)+".log";
	std::string sEnd="\13\10";
	std::ofstream out;
	out.open(sFile.c_str(), std::ios::app);
	out << msg<<std::endl;
}