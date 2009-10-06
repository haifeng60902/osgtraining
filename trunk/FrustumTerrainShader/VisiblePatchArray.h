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

	//������� ������ �� ������ ������� ������ ������� ������ ������ 512�
	const std::vector< dataPatch > &GetVisibleArray512(){ return m_vVisible512; };

private:
	//��������� ������� �������� ����
	void FillRootPatch();

	//���������� ������ � ��������� ������
	void Process();

	//���������� ������ � ��������� ������ ������� ������ ������ 512�
	void Process512();

	//����������� ��������� �����
	bool PatchVisible( const dataPatch &patch );

	//������� �� ��������� �������
	void ProcessPatch( const dataPatch &patch );

	//�������� ����������
	bool DistAppropriate( const dataPatch &patch );

	//�������� ����������
	bool CompareDist( const dataPatch &patch );

	//������ �������� ���������
	void Devision( const dataPatch &patch );

	//�������� ��������� ������ �� ����� �� 512�
	void Devision512( const dataPatch &patch );

	//������ ������ � ������� ������
	std::vector< dataPatch > m_vVisible;

	//������ ������ � ������� ������ ������� ������ ������ 512�
	std::vector< dataPatch > m_vVisible512;

	//������ ������������� ����������
	std::vector< dataPatch > m_vTemp0;
	std::vector< dataPatch > m_vTemp1;

	//��������� �����������
	osg::Vec3 m_Pos;
};

#endif	//_VISIBLE_PATCH_ARRAY_H_