#ifndef _RENDER_API_H_
#define _RENDER_API_H_

#include <d3d11.h>

#include "Types.h"
#include "Enums.h"

using namespace render;

class renderApi
{
public:
	void init(tUInt64 hWnd=0, int iWidth=0, int iHeight=0, bool bFullscreen=false, int iAdapter=0, int vSync=0,
		MSAA_ENUM eMsaa=MSAA_OFF);

	void close();

private:
	tUInt64 m_hWnd;
	int iWidth;

	// Three main DirectX objects used for render
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	D3D_FEATURE_LEVEL featureLevel;

	/*int iHeight=0, bool bFullscreen=false, int iAdapter=0, int vSync=0,
		MSAA_ENUM eMsaa=MSAA_OFF
		*/
};

#endif	//_RENDER_API_H_
