#include "PatchInfo.h"

#include "binData/enumTypes.h"

PatchInfo::PatchInfo()
{

}

PatchInfo::~PatchInfo()
{

}

void PatchInfo::InitPatchData()
{
	//���������������� ������ � ���������� ������
	
	binHouse _house;
	m_binPatch[ 1 ][ 3 ].m_mapHouse[ SCHOOL_106 ].push_back( _house );
}