#include "renderApi.h"

#include <iostream>

void renderApi::init(tUInt64 hWnd, int iWidth, int iHeight, bool bFullscreen, int iAdapter, int vSync,
					 MSAA_ENUM eMsaa)
{
	std::cout<<"init() "<< (int)eMsaa<<"\n";
}