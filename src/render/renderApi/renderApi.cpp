#include "renderApi.h"

#define LOG_MODULE "RENDERAPI"
#include "Log.h"

#include <iostream>

bool renderApi::init(const binRender& mBinRender)
{
	//запоминаем параметры инициализации
	m_BinRender=mBinRender;

	INT iCreateDeviceFlags = 0;
#if defined(_DEBUG) || defined(DEBUG)
	iCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Order of feature levels to attempt to create
	static const D3D_FEATURE_LEVEL ftLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

	// Create device
	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, iCreateDeviceFlags,
		ftLevels, sizeof(ftLevels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION,
		&m_DX.pD, &m_DX.ftLevel, &m_DX.pC);

	if (FAILED(hr))
	{
		LOG_ERROR("DX11Renderer::init() failed - D3D11CreateDevice() returned %s", DXGetErrorString(hr));
		return false;
	}

	return true;
}