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
	//������� ������� ����
	m_MtrTr = new osg::MatrixTransform;

	//��������� ������
	osg::ref_ptr< osg::Node > node1 = osgDB::readNodeFile( sModel );

	//��������
	m_MtrTr->setUpdateCallback( new UpdClbkAnimatingModel() );

	m_MtrTr->addChild( node1.get() );
}