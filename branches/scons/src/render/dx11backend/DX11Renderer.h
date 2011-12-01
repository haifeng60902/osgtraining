#ifndef DX11RENDERER_H
#define DX11RENDERER_H

//#include "DX11backend.h"

#include <string>

//#include "dx11backend.h"
//#include "renderer/IRenderAPI.h"

class DX11Renderer
{
public:

	DX11Renderer();

	~DX11Renderer();

	std::string getBackendName();
};

#endif
