#ifndef _UPDATE_CALLBACK_CAMERA_0_H_
#define _UPDATE_CALLBACK_CAMERA_0_H_

#include <osg/NodeCallback>
#include <osg/Vec3>

class UpdateCallbackCamera0 : public osg::NodeCallback
{
public:
	UpdateCallbackCamera0();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
};

#endif	//_UPDATE_CALLBACK_CAMERA_0_H_