#include "AnimatingModel.h"

#include "UpdClbkAnimatingModel.h"

#include <osgDB/ReadFile>

AnimatingModel::AnimatingModel()
{

}

AnimatingModel::~AnimatingModel()
{

}

void AnimatingModel::Init( std::string sModel )
{
	//создать главный узел
	m_MtrTr = new osg::MatrixTransform;

	//загрузить модель
	osg::ref_ptr< osg::Node > node1 = osgDB::readNodeFile( sModel );

	//анимация
	m_MtrTr->setUpdateCallback( new UpdClbkAnimatingModel() );

	m_MtrTr->addChild( node1.get() );
}