#include "renderApi.h"

#include <iostream>

void renderApi::init(tUInt64 hWnd, int iWidth, int iHeight, bool bFullscreen, int iAdapter, int vSync,
					 MSAA_ENUM eMsaa)
{
	INT createDeviceFlags = 0;
#if defined(_DEBUG) || defined(DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Order of feature levels to attempt to create
	static const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

	// Create device
	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
		featureLevels, sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION,
		&device, &featureLevel, &deviceContext);

	std::cout<<"ok";
}