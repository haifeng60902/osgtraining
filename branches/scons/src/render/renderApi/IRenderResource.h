#ifndef _I_RENDER_RESOURCE_H_
#define _I_RENDER_RESOURCE_H_

#include <string>

using namespace render;

/**
 * Structure to completely describe texture
 */
struct TextureDesc
{
	TextureDesc()
	{
		this->name      = "";
		this->width     = 0;
		this->height    = 0;
		this->count     = 1;
		this->mipLevels = 1;
		this->format    = FMT_A8R8G8B8;
		this->usage     = TU_UNKNOWN;
		this->type      = TT_TEXTURE2D;
		this->flags     = 0;
		this->msaa      = MSAA_OFF;
	};

	std::string sName;

	// width and height of texture in pixels
	int iWidth, iHeight;
	
	// depth in pixels for 3d textures, count of slices for texture arrays
	union
	{
		int depth;
		int count;
	};

	// number of mip levels. 0 - if you want use default value
	int mipLevels;

	FMT_ENUM format;
	TEXTUREUSAGE_ENUM usage;
	TEXTURETYPE_ENUM type;
	int flags;	// см. TEXTURE_FLAG
	MSAA_ENUM msaa;
/*
	TextureDesc(const char* name, int width, int height, int depth_count, int mipLevels, FMT_ENUM format, TEXTUREUSAGE_ENUM usage, TEXTURETYPE_ENUM type, int flags, MSAA_ENUM msaa)
	{
		this->name      = name;
		this->width     = width;
		this->height    = height;
		this->count     = depth_count;
		this->mipLevels = mipLevels;
		this->format    = format;
		this->usage     = usage;
		this->type      = type;
		this->flags     = flags;
		this->msaa      = msaa;
	}
	*/
};


#endif	//_I_RENDER_RESOURCE_H_