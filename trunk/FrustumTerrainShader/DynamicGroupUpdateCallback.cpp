#include "DynamicGroupUpdateCallback.h"

#include "dataPatch.h"

#include <iostream>
#include <fstream>

DynamicGroupUpdateCallback::DynamicGroupUpdateCallback()
{
	// ��������� �����������
}

DynamicGroupUpdateCallback::~DynamicGroupUpdateCallback()
{

}

void DynamicGroupUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//������������ ������ ������ � ������� ������
	m_VisiblePatchArray.Update();

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
				default:
					break;
				}
			}

			//�������� �������������� �������� � �������� ����
			AddChilds( group.get() );
		}
	}
}

void DynamicGroupUpdateCallback::ResetChilds()
{
	//�������� ��������� ����������� ����������� �����
	m_Node512.ResetRootNode();
	m_Node1024.ResetRootNode();
	m_Node2048.ResetRootNode();
	m_Node4096.ResetRootNode();
}

void DynamicGroupUpdateCallback::AddChilds( osg::ref_ptr< osg::Group > group )
{
	//�������� �������������� �������� � �������� ����
	group->addChild( m_Node512.getRootNode().get() );
	group->addChild( m_Node1024.getRootNode().get() );
	group->addChild( m_Node2048.getRootNode().get() );
	group->addChild( m_Node4096.getRootNode().get() );

	//������� ���������� ����� ��� ���������
	m_Node512.PrintSize();
}