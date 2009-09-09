#ifndef _VISIBLE_PATCH_ARRAY_H_
#define _VISIBLE_PATCH_ARRAY_H_

#include "dataPatch.h"

#include <osg/Vec3>

#include <vector>

class VisiblePatchArray
{
public:
	VisiblePatchArray();
	~VisiblePatchArray();
	
	//������������ ������ ������ � ������� ������
	void Update();

	//������� ������ �� ������ ������� ������
	const std::vector< dataPatch > &GetVisibleArray(){ return m_vVisible; };

private:
	//��������� ������� �������� ����
	void FillRootPatch();

	//���������� ������ � ��������� ������
	void Process();

	//����������� ��������� �����
	bool PatchVisible( const dataPatch &patch );

	//������� �� ��������� �������
	void ProcessPatch( const dataPatch &patch );

	//�������� ����������
	bool DistAppropriate( const dataPatch &patch );

	//������ ������ � ������� ������
	std::vector< dataPatch > m_vVisible;

	//������ ������������� ����������
	std::vector< dataPatch > m_vTemp0;
	std::vector< dataPatch > m_vTemp1;

	//��������� �����������
	osg::Vec3 m_Pos;
};

#endif	//_VISIBLE_PATCH_ARRAY_H_