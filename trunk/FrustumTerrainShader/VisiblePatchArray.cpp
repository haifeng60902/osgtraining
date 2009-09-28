#include "VisiblePatchArray.h"

#include "FrustumSingleton.h"

#include <iostream>

VisiblePatchArray::VisiblePatchArray()
{

}

VisiblePatchArray::~VisiblePatchArray()
{

}

void VisiblePatchArray::Update()
{
	//������������ ������ ������ � ������� ������

	//������� ��������� ���������� ����������
	m_vVisible.clear();

	//������� ��������� �����������
	m_Pos = FrustumSingleton::Instance().GetViewPos();

//	std::cout << m_Pos.x() << " "
//		<< m_Pos.y() << " "
//		<< m_Pos.z() << ";  ";

	//��������� ������� �������� ����
	FillRootPatch();

	//���������� ������ � ��������� ������
	Process();
}

void VisiblePatchArray::FillRootPatch()
{
	//��������� ������� �������� ����
	dataPatch patch;
	patch.m_iSize = 512 * 256;	//������ 1 ����� � ������, (m_iX � m_iY ����� 0 �� ���������)
	m_vTemp0.push_back( patch );	//��������� 1 ����

	patch.m_iX = 512 * 256;
	m_vTemp0.push_back( patch );	//��������� 2 ����

	patch.m_iY = 512 * 256;
	m_vTemp0.push_back( patch );	//��������� 3 ����

	patch.m_iX = 0;
	m_vTemp0.push_back( patch );	//��������� 4 ����
}

void VisiblePatchArray::Process()
{
	//���������� ������ � ��������� ������
	while( !m_vTemp0.empty() )
	{
		for ( int i = 0 ; i < m_vTemp0.size() ; ++i )
		{
			//����������� ��������� �����
			if ( PatchVisible( m_vTemp0[ i ] ) )
				//������� �� ��������� �������
				//ProcessPatch( m_vTemp0[ i ] );

				//������ �������� ���������
				Devision( m_vTemp0[ i ] );
		}

		//�������� ������
		m_vTemp0.clear();

		//�������� �������
		m_vTemp0.swap( m_vTemp1 );
	}

	//std::cout << m_vVisible.size() << " ";
}

bool VisiblePatchArray::PatchVisible( const dataPatch &patch )
{
	//����������� ��������� �����
	return FrustumSingleton::Instance().BoxVisible( osg::Vec3( patch.m_iX , patch.m_iY , -10000 ) , 
		osg::Vec3( patch.m_iX + patch.m_iSize , patch.m_iY + patch.m_iSize , 10000 ) );
}

void VisiblePatchArray::ProcessPatch( const dataPatch &patch )
{
	//������� �� ��������� �������?
	if ( !DistAppropriate( patch ) )
	{
		dataPatch downPatch;
		downPatch.m_iX = patch.m_iX;
		downPatch.m_iY = patch.m_iY;
		downPatch.m_iSize = patch.m_iSize / 2;
		m_vTemp1.push_back( downPatch );	//1 ����

		downPatch.m_iX = patch.m_iX + downPatch.m_iSize;
		m_vTemp1.push_back( downPatch );	//2 ����

		downPatch.m_iY = patch.m_iY + downPatch.m_iSize;
		m_vTemp1.push_back( downPatch );	//3 ����

		downPatch.m_iX = patch.m_iX;
		m_vTemp1.push_back( downPatch );	//4 ����
	}
}

void VisiblePatchArray::Devision( const dataPatch &patch )
{
	//������ �������� ���������
	bool bOk = CompareDist( patch );

	if ( bOk )
	{
		if ( patch.m_iSize == 512 )
			m_vVisible.push_back( patch );
		else
		{
			dataPatch downPatch;
			downPatch.m_iX = patch.m_iX;
			downPatch.m_iY = patch.m_iY;
			downPatch.m_iSize = patch.m_iSize / 2;
			m_vTemp1.push_back( downPatch );	//1 ����

			downPatch.m_iX = patch.m_iX + downPatch.m_iSize;
			m_vTemp1.push_back( downPatch );	//2 ����

			downPatch.m_iY = patch.m_iY + downPatch.m_iSize;
			m_vTemp1.push_back( downPatch );	//3 ����

			downPatch.m_iX = patch.m_iX;
			m_vTemp1.push_back( downPatch );	//4 ����
		}
	}
	else
		m_vVisible.push_back( patch );
}

bool VisiblePatchArray::DistAppropriate( const dataPatch &patch )
{
//�������� ����������
//////////////////////////////////////////////////////////////////////////
	std::vector< dataPatch > vTemp;

	dataPatch downPatch;
	downPatch.m_iX = patch.m_iX;
	downPatch.m_iY = patch.m_iY;
	downPatch.m_iSize = patch.m_iSize / 2;
	vTemp.push_back( downPatch );	//1 ����

	downPatch.m_iX = patch.m_iX + downPatch.m_iSize;
	vTemp.push_back( downPatch );	//2 ����

	downPatch.m_iY = patch.m_iY + downPatch.m_iSize;
	vTemp.push_back( downPatch );	//3 ����

	downPatch.m_iX = patch.m_iX;
	vTemp.push_back( downPatch );	//4 ����
//////////////////////////////////////////////////////////////////////////

	for ( int i = 0 ; i < 4 ; ++i )
	{
		//�������� ����������
		bool bOK = CompareDist( vTemp[ i ] );
		//bool bOK = CompareDist( patch );
		if (  bOK )
		{
			if ( patch.m_iSize == 512 )
			{
				//��� ��������� �������, �������� � ������ ������ �� �����������
				m_vVisible.push_back( patch );
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	m_vVisible.push_back( patch );

	return true;
}

bool VisiblePatchArray::CompareDist( const dataPatch &patch )
{
	//�������� ���������� �� 4-� ����� �����, ���� ���������� �� 1-��� �� �����
	//������ �������� �������, �� ���� ���������� ���������� ��������� �� ����� ������ ����
	osg::Vec3 vec_dist0( patch.m_iX - m_Pos.x() , 
		patch.m_iY - m_Pos.y(), 0 );

	osg::Vec3 vec_dist1( patch.m_iX + patch.m_iSize - m_Pos.x() , 
		patch.m_iY - m_Pos.y(), 0 );

	osg::Vec3 vec_dist2( patch.m_iX + patch.m_iSize - m_Pos.x() , 
		patch.m_iY + patch.m_iSize - m_Pos.y(), 0 );

	osg::Vec3 vec_dist3( patch.m_iX - m_Pos.x() , 
		patch.m_iY + patch.m_iSize - m_Pos.y(), 0 );

	double dist0 = vec_dist0.length();
	double dist1 = vec_dist1.length();
	double dist2 = vec_dist2.length();
	double dist3 = vec_dist3.length();

	double radius = patch.m_iSize * 2.0;

	bool bOK0 = false, bOK1 = false , bOK2 = false , bOK3 = false;

	if ( dist0 < radius )
		bOK0 = true;
	if ( dist1 < radius )
		bOK1 = true;
	if ( dist2 < radius )
		bOK2 = true;
	if ( dist3 < radius )
		bOK3 = true;

	return ( bOK0 || bOK1 || bOK2 || bOK3 );
}