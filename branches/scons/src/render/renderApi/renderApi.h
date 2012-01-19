#ifndef _RENDER_API_H_
#define _RENDER_API_H_

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
	HWND m_hWnd;
	int iWidth;
	int iHeight=0, bool bFullscreen=false, int iAdapter=0, int vSync=0,
		MSAA_ENUM eMsaa=MSAA_OFF
};

#endif	//_RENDER_API_H_
