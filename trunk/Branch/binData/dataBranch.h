#ifndef _DATA_BRANCH_H_
#define _DATA_BRANCH_H_

#include <vector>
#include <string>

struct dataLOD
{
	dataLOD() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;			//�������� ����� �����
	std::vector< float > m_vCoords;		//���������� ������, ������������� ������ (�� 3 float ���������� �� �������, x-y-z)
	std::vector< float > m_vNormals;	//�������	(�� 3 float ���������� �� ������� ,x-y-z)
	std::vector< float > m_vTexCoords0;	//���������� ���������� (�� 4 float ���������� �� ������� ,s-t-weight-matrix index)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP ��������
};

struct dataBranch
{
	dataBranch()
	{};

	std::string m_sTexture;				//�������� ������

	//������ ��������� LOD'��
	std::vector< dataLOD > m_vLOD;
};

#endif	//_DATA_BRANCH_H_