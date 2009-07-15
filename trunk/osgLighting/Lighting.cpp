#include "Lighting.h"

#include <osgDB/ReadFile>

Lighting::Lighting()
{
	buildScene();
}

Lighting::~Lighting()
{

}

void Lighting::buildScene()
{
	// the root of our scenegraph.
	m_rootGroup = new osg::Group;

	// Load the cow model.
	m_rootGroup->addChild( LoadModel().get() );
}

osg::ref_ptr< osg::Node > Lighting::LoadModel()
{
	//загрузить модель
	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile( "cow.osg" );

	return model.get();
}