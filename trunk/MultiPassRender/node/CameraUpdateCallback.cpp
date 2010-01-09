#include "CameraUpdateCallback.h"

CameraUpdateCallback::CameraUpdateCallback()
{

}

void CameraUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{

	traverse(node,nv);
}