#ifndef _DYNAMIC_HOUSE_UPDATE_CALLBACK_H_
#define _DYNAMIC_HOUSE_UPDATE_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Geode>

class DynamicHouseUpdateCallback : public osg::NodeCallback
{
public:
	DynamicHouseUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );
};

#endif	//_DYNAMIC_HOUSE_UPDATE_CALLBACK_H_