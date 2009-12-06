#ifndef _BIN_BRANCH_H_
#define _BIN_BRANCH_H_

#include <vector>
#include <string>

typedef std::vector< float > tVecVertex;
typedef std::vector< unsigned short > tVecIndex;
typedef std::vector< tVecIndex > tVecVecIndex;

struct binBranchGeom
{
	binBranchGeom() : m_fAlfa( 0.0f)
	{};

	//���������� ������: 3 �������� �� �������
	tVecVertex m_vVertex;

	//������� � �������: 3 �������� �� �������
	tVecVertex m_vNormal;

	//���������� ���������� �������: 2 �������� �� �������
	tVecVertex m_vTexCoord;

	//������� ������ ��� ������ TRIANGLE_STRIP
	tVecVecIndex m_vvIndex;

	//�������� �����-�����
	float m_fAlfa;
};

//����� ��������� ��� LOD'��
typedef std::vector< binBranchGeom > tVecBranch;

struct binBranch
{
	//LOD'� ������
	tVecBranch m_vBranch;

	//��� ����� � ��������� ������
	std::string m_sTexture;
};

#endif	//_BIN_BRANCH_H_