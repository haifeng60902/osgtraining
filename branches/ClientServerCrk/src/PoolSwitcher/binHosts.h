#ifndef _BIN_HOSTS_H_
#define _BIN_HOSTS_H_

#include <vector>
#include <string>

struct binHosts
{
	binHosts():bBat(false)
	{
	};
	std::string sHost;
	std::string sUser;
	std::string sPass;
	std::string sPath;
	std::string sExec;
	std::string sMiner;
	bool bBat;
};

typedef std::vector<binHosts> tVecHosts;

#endif	//_BIN_HOSTS_H_