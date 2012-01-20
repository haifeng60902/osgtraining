#ifndef _ENUMS_H_
#define _ENUMS_H_

namespace render
{

enum MSAA_ENUM
{
	MSAA_OFF	= 0,
	MSAA_2x		= 1,
	MSAA_4x		= 2,
	MSAA_8x		= 3,
	MSAA_16x	= 4,
	MSAA_8xQ	= 5,
	MSAA_16xQ	= 6
};

enum FMT_ENUM
{
	FMT_UNKNOWN              = 0,

	FMT_R8G8B8               = 20,
	FMT_A8R8G8B8             = 21,
	FMT_X8R8G8B8             = 22,
	FMT_R5G6B5               = 23,
	FMT_X1R5G5B5             = 24,
	FMT_A1R5G5B5             = 25,
	FMT_A4R4G4B4             = 26,
	FMT_R3G3B2               = 27,
	FMT_A8                   = 28,
	FMT_A8R3G3B2             = 29,
	FMT_X4R4G4B4             = 30,
	FMT_A2B10G10R10          = 31,
	FMT_A8B8G8R8             = 32,
	FMT_X8B8G8R8             = 33,
	FMT_G16R16               = 34,
	FMT_A2R10G10B10          = 35,
	FMT_A16B16G16R16         = 36,
	// Only for directx11. There is not such format in directx9. See "Legacy Formats: Map Direct3D 9 Formats to Direct3D 10"
	FMT_R8                   = 50,


	FMT_R32T                 = 70,


	FMT_D32                  = 71,
	FMT_D15S1                = 73,
	FMT_D24S8                = 75,
	FMT_D24X8                = 77,
	FMT_D24X4S4              = 79,
	FMT_D16                  = 80,

	FMT_D32F_LOCKABLE        = 82,
	FMT_D24FS8               = 83,

	// s10e5 formats (16-bits per channel)
	FMT_R16F                 = 111,
	FMT_G16R16F              = 112,
	FMT_A16B16G16R16F        = 113,

	// IEEE s23e8 formats (32-bits per channel)
	FMT_R32F                 = 114,
	FMT_G32R32F              = 115,
	FMT_A32B32G32R32F        = 116,

	// Block compressed textures
	FMT_BC1                  = 0x31545844,
	FMT_BC2                  = 0x33545844,
	FMT_BC3                  = 0x35545844,
	FMT_BC4                  = 0x37545844,
	FMT_BC5                  = 0x39545844,
};

// Texture::create()
enum TEXTUREUSAGE_ENUM
{
	TU_UNKNOWN				= 0,
	TU_READ_PS_STATIC		= 1,	// адресуется в пиксельном шейдере (обновляется 1 раз)
	TU_READ_PS_DYNAMIC		= 2,	// адресуется в пиксельном шейдере (обновляется много раз)
	TU_READ_VS_STATIC		= 3,	// адресуется в вертексном шейдера (вертексная текстура) (обновляется 1 раз)
	TU_READ_VS_DYNAMIC		= 4,	// адресуется в вертексном шейдера (вертексная текстура) (обновляется много раз)
	TU_READ_GPUCPU_DYNAMIC	= 5,	// обновляется много раз, читается с GPU
	TU_READ_CPU				= 6,	// читается программно на CPU
};

// FrameBuffer::addColor()
enum TEXTURETYPE_ENUM
{
	TT_TEXTURE1D = 0,
	TT_TEXTURE2D,
	TT_TEXTURE3D,
	TT_TEXTUREARRAY,
	TT_TEXTURECUBE,
};

}		//namespace render
#endif	//_ENUMS_H_