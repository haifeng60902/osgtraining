#include "SimpleScene.h"

#include "CullCallback.h"

#include <osg/Geode>
#include <osg/ShapeDrawable>

SimpleScene::SimpleScene()
{
	m_rootNode = new osg::Group;

	//���������������� ���������
	InitGeom();

	m_rootNode->setCullCallback( new CullCallback );
}

SimpleScene::~SimpleScene()
{

}

void SimpleScene::InitGeom()
{
	//���������������� ���������
	osg::Geode* geode = new osg::Geode();

	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),2.0f)));

	m_rootNode->addChild( geode );
}