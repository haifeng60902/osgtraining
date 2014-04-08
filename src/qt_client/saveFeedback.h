#ifndef _SAVE_FEEDBACK_H_
#define _SAVE_FEEDBACK_H_

#include <string>
#include "binMiner.h"

class saveFeedback
{
public:
	saveFeedback();
	~saveFeedback();

	//set log path
	void setLogPath(const std::string path){sLogPath=path;};

	//save string to log
	void parse(eMinerMode mode, const std::string& msg);

private:
	void saveSummary(const std::string& msg);

	//check directory exist
	bool directoryExists(const char* dirName);

	std::string sLogPath;
};

#endif	//_SAVE_FEEDBACK_H_