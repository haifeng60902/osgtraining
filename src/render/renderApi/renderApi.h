#ifndef _RENDER_API_H_
#define _RENDER_API_H_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "binRender.h"
#include "binDX.h"

using namespace render;

class renderApi
{
public:
	bool init(const binRender& mBinRender=binRender());

	void close();

private:
	//параметры инициализации
	binRender m_BinRender;

	// main DirectX objects used for render
	binDX m_DX;
};

#endif	//_RENDER_API_H_
