#ifndef _CAMERA_PLANE_CALLBACK_H_
#define _CAMERA_PLANE_CALLBACK_H_

#include <osg/NodeCallback>

class CameraPlaneCallback : public osg::NodeCallback
{
public:
	CameraPlaneCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

};

#endif	//_CAMERA_PLANE_CALLBACK_H_