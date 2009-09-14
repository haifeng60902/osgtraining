#ifndef _DATA_LEAF_H_
#define _DATA_LEAF_H_

#include <vector>
#include <string>

struct dataLfLOD
{
	dataLfLOD() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;				//�������� ����� �����

	std::vector< float > m_vCoords;		//���������� ������, ������������� ������ (�� 3 float ���������� �� �������, x-y-z)
	std::vector< float > m_vNormals;	//�������	(�� 3 float ���������� �� ������� ,x-y-z)
	std::vector< float > m_vTexCoords0;	//���������� ���������� (�� 4 float ���������� �� ������� ,s-t-weight-matrix index)
	std::vector< float > m_vTexCoords1;	//���������� ���������� (�� 3 float ���������� �� ������� ,size_x - size_y - map_index )

};

struct dataLeaf
{
	dataLeaf() : m_fFreqY( 0.0f )
		, m_fAmplY( 0.0f )
		, m_fFreqZ( 0.0f )
		, m_fAmplZ( 0.0f )
	{};

	std::vector< std::string > m_vTextures;	//�������� �����

	//������ ��������� LOD'�� ������
	std::vector< dataLfLOD > m_vLfLOD;

	float m_fFreqY;						//������� �������� ������ ������ ��� Y
	float m_fAmplY;						//��������� �������� ������ ������ ��� Y
	float m_fFreqZ;						//������� �������� ������ ������ ��� Z
	float m_fAmplZ;						//��������� �������� ������ ������ ��� Z
};

#endif	//_DATA_LEAF_H_