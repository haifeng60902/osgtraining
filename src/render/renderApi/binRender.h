#ifndef _BIN_RENDER_H_
#define _BIN_RENDER_H_

#include "Types.h"
#include "Enums.h"

struct binRender
{
	binRender():hWnd(0),
		iWidth(0),
		iHeight(0),
		bFullscreen(false),
		iAdapter(0),
		vSync(0),
		eMsaa(render::MSAA_OFF)
	{};

	tUInt64 hWnd;
	int iWidth;
	int iHeight;
	bool bFullscreen;
	int iAdapter;
	int vSync;
	render::MSAA_ENUM eMsaa;
};

#endif	//_BIN_RENDER_H_