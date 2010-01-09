#ifndef _CAMERA_UPDATE_CALLBACK_H_
#define _CAMERA_UPDATE_CALLBACK_H_

#include <osg/NodeCallback>

class CameraUpdateCallback : public osg::NodeCallback
{
public:
	CameraUpdateCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
};

#endif	//_CAMERA_UPDATE_CALLBACK_H_