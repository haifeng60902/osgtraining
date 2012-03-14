//#include <iostream>

//#include <windows.h>
//#include <Winuser.h>
//#include "DX11Renderer.h"

#include "renderApi.h"

extern "C" {
#    include "lua.h"
#    include "lauxlib.h"
#    include "lualib.h"
}

int main()
{
	int status;
	lua_State *L;
	L = lua_open();//������� ����
	luaL_openlibs(L);//���������� ����������� ����������   
	//status = luaL_loadfile(L, "script.lua");//��������� ����
	
	renderApi pApi;
	
	pApi.init();

/*
	DX11Renderer *dx11=new DX11Renderer();

	std::cout << dx11->getBackendName() << "\n";

	//GetActiveWindow();

	bool bRes=dx11->InitDevice(512,512);

	delete dx11;
	*/
}