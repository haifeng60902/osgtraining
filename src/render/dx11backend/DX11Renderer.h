#ifndef DX11RENDERER_H
#define DX11RENDERER_H

//#include "DX11backend.h"

#include <string>
#include <d3d11.h>

//#include "dx11backend.h"
//#include "renderer/IRenderAPI.h"

class DX11Renderer
{
public:

	DX11Renderer();

	~DX11Renderer();

	//инициализация девайса
	bool InitDevice(int iX, int iY);

	std::string getBackendName();

private:
	void Get();
};

#endif
