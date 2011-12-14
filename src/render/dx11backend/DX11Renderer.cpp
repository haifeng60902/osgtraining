#include "DX11Renderer.h"

DX11Renderer::DX11Renderer()
{

}

DX11Renderer::~DX11Renderer()
{

}

std::string DX11Renderer::getBackendName()
{
	return std::string("DX11Renderer");
}

bool DX11Renderer::InitDevice(int iX, int iY)
{
	//инициализация девайса
	//инициализация девайса
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	return true;
}