#include "DynamicGroupUpdateCallback.h"

#include "dataPatch.h"
#include "FrustumSingleton.h"

#include <iostream>
#include <fstream>

DynamicGroupUpdateCallback::DynamicGroupUpdateCallback( osg::ref_ptr< osg::Uniform > _unfVisPos )
{
	// ��������� �����������
	m_unfVisPos = _unfVisPos;
}

DynamicGroupUpdateCallback::~DynamicGroupUpdateCallback()
{

}

void DynamicGroupUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//������������ ������ ������ � ������� ������
	m_VisiblePatchArray.Update();

	//�������� ��������� ����������� ��� ���������� ������ �������
	UpdateShaderPos();

	//�������� ����������
	UpdateStatistic();

	osg::ref_ptr< osg::Group > group = dynamic_cast< osg::Group* >( node );

	if ( group )
	{
		//������� ������ �� ������ ������� ������
		const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

		if ( !data_vis.empty() )
		{
			//�������� ���� �����
			group->removeChildren( 0 , group->getNumChildren() );

			//�������� ��������� ����������� ����������� �����
			ResetChilds();

			//��������� ��� ������� ����
			for( int i = 0 ; i < data_vis.size() ; ++i )
			{
				switch( data_vis[ i ].m_iSize )
				{
				case 512:
					m_Node512.AddPatch( data_vis[ i ].m_iX , data_vis[ i ].m_iY );
					break;
				case 1024:
					m_Node1024.AddPatch( data_vis[ i ].m_iX , data_vis[ i ].m_iY );
					break;
				case 2048:
					m_Node2048.AddPatch( data_vis[ i ].m_iX , data_vis[ i ].m_iY );
					break;
				case 4096:
					m_Node4096.AddPatch( data_vis[ i ].m_iX , data_vis[ i ].m_iY );
					break;
				case 8192:
					m_Node8192.AddPatch( data_vis[ i ].m_iX , data_vis[ i ].m_iY );
					break;
				case 16384:
					m_Node16384.AddPatch( data_vis[ i ].m_iX , data_vis[ i ].m_iY );
					break;
				case 32768:
					m_Node32768.AddPatch( data_vis[ i ].m_iX , data_vis[ i ].m_iY );
					break;
				default:
					break;
				}
			}

			//�������� �������������� �������� � �������� ����
			AddChilds( group.get() );
		}
	}
}

void DynamicGroupUpdateCallback::UpdateShaderPos()
{
	//�������� ��������� ����������� ��� ���������� ������ �������
	osg::Vec3 pos = FrustumSingleton::Instance().GetViewPos();
	m_unfVisPos->set( pos );
}

void DynamicGroupUpdateCallback::ResetChilds()
{
	//�������� ��������� ����������� ����������� �����
	m_Node512.ResetRootNode();
	m_Node1024.ResetRootNode();
	m_Node2048.ResetRootNode();
	m_Node4096.ResetRootNode();
	m_Node8192.ResetRootNode();
	m_Node16384.ResetRootNode();
	m_Node32768.ResetRootNode();
}

void DynamicGroupUpdateCallback::AddChilds( osg::ref_ptr< osg::Group > group )
{
	//�������� �������������� �������� � �������� ����
	group->addChild( m_Node512.getRootNode().get() );
	group->addChild( m_Node1024.getRootNode().get() );
	group->addChild( m_Node2048.getRootNode().get() );
	group->addChild( m_Node4096.getRootNode().get() );
	group->addChild( m_Node8192.getRootNode().get() );
	group->addChild( m_Node16384.getRootNode().get() );
	group->addChild( m_Node32768.getRootNode().get() );

	//������� ���������� ����� ��� ���������
//	m_Node512.PrintSize();
}

void DynamicGroupUpdateCallback::UpdateStatistic()
{
	//�������� ����������

	//������� ������ �� ������ ������� ������
	const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

	if ( data_vis.size() > 0 )
	{
		std::map< int , int > _Statistic;

		//��������� ��� ������� ����
		for( int i = 0 ; i < data_vis.size() ; ++i )
			_Statistic[ data_vis[ i ].m_iSize ]++;

		if ( m_Statistic.empty() )
			m_Statistic = _Statistic;

		bool bUpdate = false;
		std::map< int , int > ::iterator it = _Statistic.begin();
		while( it != _Statistic.end() )
		{
			if ( m_Statistic[ it->first ] < it->second )
			{
				m_Statistic[ it->first ] = it->second;
				bUpdate = true;
			}

			++it;
		}

		if ( bUpdate )
		{

			std::map< int , int > ::iterator it = m_Statistic.begin();
			while( it != m_Statistic.end() )
			{
				std::cout << it->first << "-" << it->second << "\t";

				++it;
			}
			std::cout << "\n";
		}
	}
}