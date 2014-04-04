#ifndef _SAVE_FEEDBACK_H_
#define _SAVE_FEEDBACK_H_

#include <string>

class saveFeedback
{
public:
	saveFeedback();
	~saveFeedback();

	//set log path
	void setLogPath(const std::string path){sLogPath=path;};

	//save string to log
	void parse(const std::string mode, const std::string msg);

private:
	std::string sLogPath;
};

#endif	//_SAVE_FEEDBACK_H_