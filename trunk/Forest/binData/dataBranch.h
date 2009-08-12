#ifndef _DATA_BRANCH_H_
#define _DATA_BRANCH_H_

#include <vector>
#include <string>

//��������
struct dataBranch
{
	dataBranch() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;			//�������� ����� �����
	std::string m_sTexture;				//�������� ������
	std::vector< float > m_vCoords;		//���������� ������, ������������� ������ (�� 4 float ���������� �� �������, x-y-z-WindWeights)
	std::vector< float > m_vNormals;	//�������	(�� 4 float ���������� �� ������� ,x-y-z-WindMatrixIndices)
	std::vector< float > m_vTexCoords0;	//���������� ���������� (�� 2 float ���������� �� ������� ,x-y)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP ��������
};

#endif	//_DATA_BRANCH_H_