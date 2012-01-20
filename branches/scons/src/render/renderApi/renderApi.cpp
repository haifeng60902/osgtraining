#include "renderApi.h"

#include <iostream>
#include <assert.h>

#define LOG_MODULE "RENDERAPI"
#include "Log.h"

renderApi::renderApi():m_bInit(false)
{

}

renderApi::~renderApi()
{

}

bool renderApi::init(const binRender& mBinRender)
{
	if (m_bInit)
		return true;

	//запоминаем параметры инициализации
	m_BinRender=mBinRender;

	// Если не в фулскрине то получаем высоту и ширину окошка
	RECT mClientRect;
	GetClientRect((HWND)mBinRender.hWnd, &mClientRect);

	if (!m_BinRender.bFullscreen)
	{
		m_BinRender.iWidth = mClientRect.right - mClientRect.left;
		m_BinRender.iHeight = mClientRect.bottom - mClientRect.top;
	}

	// создаем девайс
	if (FAILED(InitDevice(m_BinRender)))
	{
		Shutdown();
		return false;
	}

	if (!InitializeScreenFrameBuffer(m_BinRender.iWidth, m_BinRender.iHeight))
		return false;

	return true;
}

HRESULT renderApi::InitDevice(const binRender& mBinRender)
{
	//инициализация device
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

	// Multisample settings
	DXGI_SAMPLE_DESC mSampleDesc = {1, 0};
	CheckMSAA(FMT_A8R8G8B8, mBinRender.eMsaa, mSampleDesc);

	// Create swap chain for device
	DXGI_SWAP_CHAIN_DESC sd; ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount       = 1; // For SLI and Crossfire
	sd.BufferDesc.Width  = m_BinRender.iWidth;
	sd.BufferDesc.Height = m_BinRender.iHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed          = !m_BinRender.bFullscreen;
	sd.OutputWindow      = (HWND)m_BinRender.hWnd;
	sd.SampleDesc        = mSampleDesc;
	sd.BufferDesc.RefreshRate.Numerator   = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	// Swap chain must be created by the same IDXGIFactory as device
	IDXGIFactory* dxgiFactory = GetDeviceFactory(m_DX.pD);
	if (dxgiFactory == NULL)
	{
		ERROR("DX11Renderer::init() failed - failed to get IDXGIFactory from ID3D11Device");
		return E_FAIL;
	}

	hr = dxgiFactory->CreateSwapChain(m_DX.pD, &sd, &m_DX.pSC);
	SAFE_RELEASE(dxgiFactory);

	if (FAILED(hr))
	{
		LOG_ERROR("DX11Renderer::init() failed - IDXGIFactory::CreateSwapChain() returned %s", DXGetErrorString(hr));
		return hr;
	}

	return hr;
}

/**
* Create screen frame buffer
*/
bool renderApi::InitializeScreenFrameBuffer(int iWidth, int iHeight)
{
	// Create screen buffer texture
	ID3D11Texture2D* pTexture = NULL;
	HRESULT hr = m_DX.pSC->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pTexture);
	if (FAILED(hr))
		return false;

	ID3D11RenderTargetView* pRenderTargetView = NULL;
	hr = m_DX.pD->CreateRenderTargetView(pTexture, NULL, &pRenderTargetView);
	if (FAILED(hr))
		return false;


	// Add default viewport
	D3D11_VIEWPORT defaultViewport = { 0.0f, 0.0f, (FLOAT)iWidth, (FLOAT)iHeight, 0.0f, 1.0f };
	//screenFrameBuffer->viewportStack.push(defaultViewport);

	return true;
}

bool renderApi::CheckMSAA(FMT_ENUM eFormat, MSAA_ENUM eAntialiasing, DXGI_SAMPLE_DESC& mSampleDesc)
{
	// Multisample settings
	assert(m_DX.pD != NULL);

	UINT uiSampleCount = 1, uiQualityLevels = 0, uiMaxQualityLevels = 0;

	switch (eAntialiasing)
	{
	case MSAA_2x:   uiSampleCount = 2; uiQualityLevels = 0;  break;
	case MSAA_4x:   uiSampleCount = 4; uiQualityLevels = 4;  break;
	case MSAA_8x:   uiSampleCount = 4; uiQualityLevels = 8;  break;
	case MSAA_8xQ:  uiSampleCount = 8; uiQualityLevels = 8;  break;
	case MSAA_16x:  uiSampleCount = 4; uiQualityLevels = 16; break;
	case MSAA_16xQ: uiSampleCount = 8; uiQualityLevels = 16; break;
	}

	HRESULT hr = m_DX.pD->CheckMultisampleQualityLevels(GetDXGIFormat(eFormat), uiSampleCount, &uiMaxQualityLevels);

	if (uiMaxQualityLevels == 0)
	{
		mSampleDesc.Count   = 1;
		mSampleDesc.Quality = 0;
		return false;
	}

	uiQualityLevels = std::min(uiQualityLevels, uiMaxQualityLevels - 1);

	mSampleDesc.Count   = uiSampleCount;
	mSampleDesc.Quality = uiQualityLevels;
	return true;
}

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
DXGI_FORMAT renderApi::GetDXGIFormat(FMT_ENUM eFormat, int iMode)
{
	switch (eFormat)
	{
	case FMT_A8:			return DXGI_FORMAT_A8_UNORM;
	case FMT_A8R8G8B8:      return DXGI_FORMAT_R8G8B8A8_UNORM;
	case FMT_A16B16G16R16:  return DXGI_FORMAT_R16G16B16A16_UNORM;
	case FMT_A16B16G16R16F: return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case FMT_A32B32G32R32F: return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case FMT_A2R10G10B10:	return DXGI_FORMAT_R10G10B10A2_UNORM;
	case FMT_G32R32F:       return DXGI_FORMAT_R32G32_FLOAT;
	case FMT_R8:			return DXGI_FORMAT_R8_UNORM;
	case FMT_R32F:			return DXGI_FORMAT_R32_FLOAT;
	case FMT_R16F:			return DXGI_FORMAT_R16_FLOAT;
	case FMT_BC1:           return DXGI_FORMAT_BC1_UNORM;
	case FMT_BC2:           return DXGI_FORMAT_BC2_UNORM;
	case FMT_BC3:           return DXGI_FORMAT_BC3_UNORM;
	case FMT_BC4:           return DXGI_FORMAT_BC4_UNORM;
	case FMT_BC5:           return DXGI_FORMAT_BC5_UNORM;
	case FMT_D24S8:         
		{
			if (iMode == 0) return DXGI_FORMAT_D24_UNORM_S8_UINT;
			if (iMode == 1) return DXGI_FORMAT_R24G8_TYPELESS;
			if (iMode == 2) return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		}
	case FMT_D32:
		{
			if (iMode == 0) return DXGI_FORMAT_D32_FLOAT;
			if (iMode == 1) return DXGI_FORMAT_R32_TYPELESS;
			if (iMode == 2) return DXGI_FORMAT_R32_FLOAT;
		}
	case FMT_R32T:
		{
			if (iMode == 0) return DXGI_FORMAT_D32_FLOAT;
			if (iMode == 1) return DXGI_FORMAT_R32_TYPELESS;
			if (iMode == 2) return DXGI_FORMAT_R32_FLOAT;
		}
	default:                assert(false && "unknown format");
	}

	return DXGI_FORMAT_UNKNOWN; // never gets here
}

/**
* For specified ID3D11Device returns IDXGIFactory used to create it
*/
IDXGIFactory* renderApi::GetDeviceFactory(ID3D11Device* pD)
{
	assert(pD != NULL);

	IDXGIDevice*  dxgiDevice  = NULL;
	IDXGIFactory* dxgiFactory = NULL;
	IDXGIAdapter* dxgiAdapter = NULL;

	HRESULT hr = pD->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	if (SUCCEEDED(hr))
	{
		hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
		if (SUCCEEDED(hr))
		{
			hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
		}
	}

	SAFE_RELEASE(dxgiAdapter);
	SAFE_RELEASE(dxgiDevice);

	return dxgiFactory;
}

/**
* Shutdown renderer and release all resources
*/
void renderApi::Shutdown()
{
	// Than release all DirectX objects
	if (m_DX.pC != NULL)
		m_DX.pC->ClearState();

	// You may not release a swap chain in full-screen mode because doing so may create thread contention
	// (which will cause DXGI to raise a non-continuable exception). Before releasing a swap chain, first
	// switch to windowed mode (c) DirectX SDK Documentation
	if (m_DX.pSC != NULL)
		m_DX.pSC->SetFullscreenState(FALSE, NULL);

	SAFE_RELEASE(m_DX.pSC);
	SAFE_RELEASE(m_DX.pC);
	SAFE_RELEASE(m_DX.pD);
}
