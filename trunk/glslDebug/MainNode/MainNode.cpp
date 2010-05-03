#include "MainNode.h"

#include "UpdClbkMainNode.h"

#include <osgDB/ReadFile>
#include <osg/Referenced>
#include <osg/Group>
#include <osg/MatrixTransform>

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

	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );

	//�������� �������� ���������
	m_Group->addChild( node.get() );

	m_Triangle = new Triangle();
	m_Triangle->Init();
	m_Group->addChild( m_Triangle->GetNode().get() );

	//������ �������� ����� ���������� �������� ���� ��� ������� ���������� ������
	m_Group->setUpdateCallback( new UpdClbkMainNode() );
}