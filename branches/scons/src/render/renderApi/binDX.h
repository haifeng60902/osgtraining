#ifndef _BIN_DX_H_
#define _BIN_DX_H_

struct binDX
{
	binDX():pD(NULL)
		,pC(NULL)
	{};

	// Three main DirectX objects used for render
	ID3D11Device* pD;
	ID3D11DeviceContext* pC;
	D3D_FEATURE_LEVEL ftLevel;
};

#endif	//_BIN_DX_H_