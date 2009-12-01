#ifndef _BIN_BRANCH_H_
#define _BIN_BRANCH_H_

#include <vector>

typedef std::vector< float > tVecVertex;
typedef std::vector< unsigned short > tVecIndex;

struct binBranchGeom
{
	//���������� ������: 3 �������� �� �������
	tVecVertex m_vVertex;

	//������� � �������: 3 �������� �� �������
	tVecVertex m_vNormal;

	//���������� ���������� �������: 2 �������� �� �������
	tVecVertex m_vTexCoord;

	//������� ������ ��� ������ TRIANGLE_STRIP
	tVecIndex m_vIndex;
};

//����� ��������� ��� LOD'��
typedef std::vector< binBranchGeom > tVecBranch;

struct binBranch
{
	//LOD'� ������
	tVecBranch m_vBranch;
};

#endif	//_BIN_BRANCH_H_