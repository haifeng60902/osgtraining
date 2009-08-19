#ifndef _SIMPLE_UPDATE_CALLBACK_H_
#define _SIMPLE_UPDATE_CALLBACK_H_

#include <osg/Camera>
#include <osg/NodeCallback>

class SimpleUpdateCallback : public osg::NodeCallback
{
public:
	SimpleUpdateCallback( osg::Camera *_pCamera );
	~SimpleUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	osg::Camera *m_pCamera;
};

#endif	//_SIMPLE_UPDATE_CALLBACK_H_