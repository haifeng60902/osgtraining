#include "SimpleUpdateCallback.h"

SimpleUpdateCallback::SimpleUpdateCallback( osg::Camera *_pCamera ) : m_pCamera( _pCamera )
{

}

SimpleUpdateCallback::~SimpleUpdateCallback()
{

}

void SimpleUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	m_pCamera->getProjectionMatrix();


	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);
}