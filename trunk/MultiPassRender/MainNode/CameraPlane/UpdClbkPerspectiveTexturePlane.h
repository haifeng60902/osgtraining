#ifndef _UPD_CLBK_PERSPECTIVE_TEXTURE_PLANE_H_
#define _UPD_CLBK_PERSPECTIVE_TEXTURE_PLANE_H_

#include <osg/NodeCallback>

class UpdClbkPerspectiveTexturePlane : public osg::NodeCallback
{
public:
	UpdClbkPerspectiveTexturePlane();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

};

#endif	//_UPD_CLBK_PERSPECTIVE_TEXTURE_PLANE_H_