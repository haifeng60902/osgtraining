#ifndef _PATCH_INFO_H_
#define _PATCH_INFO_H_

#include "Singleton.h"
#include "binData/binPatch.h"

class PatchInfo : public Singleton< PatchInfo >
{
public:
	PatchInfo();
	~PatchInfo();

private:
	//тайлы сгрупированны 16 на 16
	binPatch m_binPatch[16][16];

};

#endif	//_PATCH_INFO_H_