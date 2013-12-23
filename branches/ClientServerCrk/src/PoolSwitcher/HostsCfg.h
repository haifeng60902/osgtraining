#ifndef _HOSTS_CFG_H_
#define _HOSTS_CFG_H_

#include "binHosts.h"

class HostsCfg
{
public:
	HostsCfg();
	~HostsCfg();

	bool Load(const char* pCfg);

	tVecHosts& GetHosts(){return vHosts;};
private:
	tVecHosts vHosts;
};

#endif	//_HOSTS_CFG_H_