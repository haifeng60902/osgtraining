#ifndef _RENDER_API_H_
#define _RENDER_API_H_

#include <Windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "binRender.h"
#include "binDX.h"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = NULL; } }
#endif

using namespace render;

class renderApi
{
public:
	renderApi();
	~renderApi();


	bool init(const binRender& mBinRender=binRender());

	void close();

private:

	//инициализация device
	HRESULT InitDevice(const binRender& mBinRender);


	/**
	* Create screen frame buffer
	*/
	bool InitializeScreenFrameBuffer(int iWidth, int iHeight);

	// Multisample settings
	bool CheckMSAA(FMT_ENUM eFormat, MSAA_ENUM eAntialiasing, DXGI_SAMPLE_DESC& mSampleDesc);

	/**
	 * For creating readable depth buffers we can not just create D24_UNORM_S8_UINT texture, 
	 * D24_UNORM_S8_UINT depth-stencil view and D24_UNORM_S8_UINT shader resource view for it.
	 * It is a DirectX limitation. We need to create R24G8_TYPELESS texture, D24_UNORM_S8_UINT 
	 * depth stencil view and DXGI_FORMAT_R24_UNORM_X8_TYPELESS shader resource view
	 *
	 * So FMT_D24S8 in normal mode (0) will return D24_UNORM_S8_UINT (will be used for depth-stencil view),
	 * in typeless mode (1) it will return R24G8_TYPELESS (will be used for creating texture),
	 * in shader-resource view mode (2) it will return R24G8_FLOAT (will be used for creating shader resource view)
	 */
	DXGI_FORMAT GetDXGIFormat(FMT_ENUM eFormat, int iMode = 0);

	/**
	 * For specified ID3D11Device returns IDXGIFactory used to create it
	 */
	IDXGIFactory* GetDeviceFactory(ID3D11Device* device);

	/**
	 * Shutdown renderer and release all resources
	 */
	void Shutdown();

	//параметры инициализации
	binRender m_BinRender;

	// main DirectX objects used for render
	binDX m_DX;

	//признак инициализации
	bool m_bInit;
};

#endif	//_RENDER_API_H_
