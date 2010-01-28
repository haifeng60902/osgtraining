#include "MainNode.h"

#include <osgDB/ReadFile>

MainNode::MainNode()
{

}

MainNode::~MainNode()
{

}

void MainNode::Init()
{
//������������� ������
	
	m_Group = new osg::Group;

	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/mi17/MI_17_lod.flt" );
	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );

	//�������� �������� ���������
	m_Group->addChild( node.get() );

	//�������� ��������� � ������������ ���������
	m_Group->addChild( m_NodePlane.GetNode().get() );
}