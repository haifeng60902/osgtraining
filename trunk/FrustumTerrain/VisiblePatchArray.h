#ifndef _VISIBLE_PATCH_ARRAY_H_
#define _VISIBLE_PATCH_ARRAY_H_

#include "dataPatch.h"

#include <vector>

class VisiblePatchArray
{
public:
	VisiblePatchArray();
	~VisiblePatchArray();
	
	//������������ ������ ������ � ������� ������
	void Update();

private:
	//������ ������ � ������� ������
	std::vector< dataPatch > m_vVisible;
};

#endif	//_VISIBLE_PATCH_ARRAY_H_