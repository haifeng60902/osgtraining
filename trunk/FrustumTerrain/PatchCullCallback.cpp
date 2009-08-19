#include "PatchCullCallback.h"

#include "FrustumSingleton.h"

PatchCullCallback::PatchCullCallback()
{

}

PatchCullCallback::~PatchCullCallback()
{

}

void PatchCullCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);
}