#include "HostsCfg.h"

#include "Core/Lua/Lua_hlp.h"

HostsCfg::HostsCfg()
{

}

HostsCfg::~HostsCfg()
{

}

bool HostsCfg::Load(const char* pCfg)
{
	lua_State* l=lua_open();
	luaL_openlibs(l);

	Lua::Config config(l);

	if (!config.dofile(pCfg))
		return false;

	if(config.open("hosts"))
	{
		config.iterate_begin();
		while(config.iterate_next())
		{
			binHosts mHost;
			mHost.sHost = config.get("host", std::string(""));
			mHost.sUser = config.get("user", std::string(""));
			mHost.sPass = config.get("pass", std::string(""));
			mHost.sPath = config.get("path", std::string(""));
			mHost.sExec = config.get("exec", std::string(""));
			mHost.sMiner= config.get("miner", std::string(""));
			vHosts.push_back(mHost);
		}
		config.iterate_end();
		config.pop();
	}

	lua_close(l);

	return true;
}