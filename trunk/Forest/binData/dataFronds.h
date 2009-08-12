#ifndef _DATA_FRONDS_H_
#define _DATA_FRONDS_H_

#include <vector>
#include <string>

struct dataFronds
{
	dataFronds() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;				//�������� ����� �����
	std::vector< std::string > m_vTextures;	//�������� �����
	std::vector< float > m_vCoords;		//���������� ������, ������������� ������ (�� 4 float ���������� �� �������, x-y-z-WindWeights)
	std::vector< float > m_vNormals;	//�������	(�� 4 float ���������� �� ������� ,x-y-z-WindMatrixIndices)
	std::vector< float > m_vTexCoords0;	//���������� ���������� (�� 2 float ���������� �� ������� ,x-y)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP ��������
};

#endif	//_DATA_FRONDS_H_