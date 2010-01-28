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
//инициализация данных
	
	m_Group = new osg::Group;

	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/mi17/MI_17_lod.flt" );
	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );

	//добавить тестовую геометрию
	m_Group->addChild( node.get() );

	//добавить плоскость с динамической текстурой
	m_Group->addChild( m_NodePlane.GetNode().get() );
}