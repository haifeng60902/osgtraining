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

	FMT_D24S8                = 75
};

}		//namespace render
#endif	//_ENUMS_H_