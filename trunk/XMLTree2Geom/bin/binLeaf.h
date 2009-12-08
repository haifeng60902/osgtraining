#ifndef _BIN_LEAF_H_
#define _BIN_LEAF_H_

#include <vector>
#include <string>

typedef std::vector< float > tVecVertex;

struct binLeafGeom
{
	binLeafGeom() : m_fAlfa( 0.0f )
	{};

	//���������� ������: 3 �������� �� �������
	tVecVertex m_vVertex;

	//������� � �������: 3 �������� �� �������
	tVecVertex m_vNormal;

	//���������� ���������� �������: 2 �������� �� �������
	tVecVertex m_vTexCoord;

	//�������� ������������ ������ �������: 2 �������� �� ������� + 1 ����� ��������
	tVecVertex m_vVerOffset;

	//�������� �����-�����
	float m_fAlfa;
};

//����� ��������� ��� LOD'��
typedef std::vector< binLeafGeom > tVecLeaf;

//����� ������� ������
typedef std::vector< std::string > tVecTexture;

struct binLeaf
{
	//LOD'� ������
	tVecLeaf m_vLeaf;

	//����� ������ � ���������� ������
	tVecTexture m_vTextures;
};

#endif	//_BIN_LEAF_H_