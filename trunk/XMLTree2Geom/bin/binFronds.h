#ifndef _BIN_FRONDS_H_
#define _BIN_FRONDS_H_

#include <vector>
#include <string>

typedef std::vector< float > tVecVertex;
typedef std::vector< unsigned short > tVecIndex;
typedef std::vector< tVecIndex > tVecVecIndex;

struct binFrondsGeom
{
	binFrondsGeom() : m_fAlfa( 0.0f)
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
typedef std::vector< binFrondsGeom > tVecFronds;

struct binFronds
{
	//LOD'� ������
	tVecFronds m_vFronds;

	//��� ����� � ��������� ������
	std::string m_sTexture;
};


#endif	//_BIN_FRONDS_H_