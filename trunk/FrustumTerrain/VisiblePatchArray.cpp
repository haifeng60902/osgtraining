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
				ProcessPatch( m_vTemp0[ i ] );
		}

		//�������� ������
		m_vTemp0.clear();

		//�������� �������
		m_vTemp0.swap( m_vTemp1 );
	}

	std::cout << m_vVisible.size() << " ";
}

bool VisiblePatchArray::PatchVisible( const dataPatch &patch )
{
	//����������� ��������� �����
	return FrustumSingleton::Instance().BoxVisible( osg::Vec3( patch.m_iX , patch.m_iY , 0 ) , 
		osg::Vec3( patch.m_iX + patch.m_iSize , patch.m_iY + patch.m_iSize , 3000 ) );
}

void VisiblePatchArray::ProcessPatch( const dataPatch &patch )
{
	//������� �� ��������� �������
	if ( ( patch.m_iSize == 512 ) && ( DistAppropriate( patch ) ) )
	{
		//��� ��������� �������, �������� � ������ ������ �� �����������
		m_vVisible.push_back( patch );
		return;
	}

	if ( patch.m_iSize == 512 )
		return;

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

//�������� ����������
bool VisiblePatchArray::DistAppropriate( const dataPatch &patch )
{
	osg::Vec3 vec_dist( patch.m_iX + patch.m_iSize * 0.5 - m_Pos.x() , 
		patch.m_iY + patch.m_iSize * 0.5 - m_Pos.y(), -m_Pos.z() );

	float dist = vec_dist.x() * vec_dist.x() + vec_dist.y() * vec_dist.y() + vec_dist.z() * vec_dist.z();

	if ( dist <= 512 * 512 )
		return true;

	return false;
}