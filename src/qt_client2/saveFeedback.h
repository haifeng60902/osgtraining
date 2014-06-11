#ifndef _SAVE_FEEDBACK_H_
#define _SAVE_FEEDBACK_H_

#include <string>
#include "core/Parse/binMiner.h"

class saveFeedback
{
public:
	saveFeedback();
	~saveFeedback();

	//set log path
	void setLogPath(const std::string path){sLogPath=path;};
	void setUser(const std::string user){sUser=user;};

	//save string to log
	void parse(eMinerMode mode, const std::string& msg);

private:
	void saveMsg(const std::string& msg, const std::string& mode);
	
	//create dir
	std::string createDir(const tm* timeinfo, const std::string& mode);

	//append string to file
	void append2File(const std::string& path, const std::string& msg, int hour);

	std::string sLogPath;
	std::string sUser;
};

#endif	//_SAVE_FEEDBACK_H_