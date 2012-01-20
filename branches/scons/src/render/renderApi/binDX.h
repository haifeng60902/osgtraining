#ifndef _BIN_DX_H_
#define _BIN_DX_H_

struct binDX
{
	binDX():pD(NULL)
		,pC(NULL)
		,pSC(NULL)
	{};

	// Three main DirectX objects used for render
	ID3D11Device* pD;
	ID3D11DeviceContext* pC;
	IDXGISwapChain* pSC;
	D3D_FEATURE_LEVEL ftLevel;
};

#endif	//_BIN_DX_H_