#ifndef _DATA_FRONDS_H_
#define _DATA_FRONDS_H_

#include <vector>
#include <string>

struct dataFrLOD
{
	dataFrLOD() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;				//�������� ����� �����

	std::vector< float > m_vCoords;		//���������� ������, ������������� ������ (�� 3 float ���������� �� �������, x-y-z)
	std::vector< float > m_vNormals;	//�������	(�� 3 float ���������� �� ������� ,x-y-z)
	std::vector< float > m_vTexCoords0;	//���������� ���������� (�� 4 float ���������� �� ������� ,s-t-weight-matrix index)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP ��������
};

struct dataFronds
{
	dataFronds() //: m_fAlphaTestValue( 0.0f )
	{};

//	float m_fAlphaTestValue;				//�������� ����� �����
	std::vector< std::string > m_vTextures;	//�������� �����

	/*
	std::vector< float > m_vCoords;		//���������� ������, ������������� ������ (�� 3 float ���������� �� �������, x-y-z)
	std::vector< float > m_vNormals;	//�������	(�� 3 float ���������� �� ������� ,x-y-z)
	std::vector< float > m_vTexCoords0;	//���������� ���������� (�� 4 float ���������� �� ������� ,s-t-weight-matrix index)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP ��������
	*/

	//������ ��������� LOD'�� �����
	std::vector< dataFrLOD > m_vFrLOD;
};

#endif	//_DATA_FRONDS_H_