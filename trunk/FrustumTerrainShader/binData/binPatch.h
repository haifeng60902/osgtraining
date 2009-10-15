#ifndef _BIN_PATCH_H_
#define _BIN_PATCH_H_

#include <vector>
#include <map>

//�������� �������-����
struct binHouse
{
	binHouse() : m_dX( 0.0 )
		, m_dY( 0.0 )
		, m_dR( 0.0 )
	{};

	//��������� ������������ �����
	double m_dX;
	double m_dY;

	//��������
	double m_dR;
};

//�������� �������-������
struct binTree
{
	binTree() : m_dX( 0.0 )
		, m_dY( 0.0 )
		, m_dR( 0.0 )
		, m_dS( 0.0 )
	{};

	//��������� ������������ �����
	double m_dX;
	double m_dY;
	
	//��������
	double m_dR;

	//���������������
	double m_dS;
};

typedef std::map< int , std::vector< binTree > > tMapTree;
typedef std::map< int , std::vector< binHouse > > tMapHouse;

struct binPatch
{
	//������ �������� ��� ������ � ������ ����, � ��������� - ������� �������� � �� ��������������
	tMapTree m_mapTree;

	//������ �������� ��� ���� � ������ ����, � ��������� - ������� ����� � �� ��������������
	tMapHouse m_mapHouse;
};

#endif	//_BIN_PATCH_H_