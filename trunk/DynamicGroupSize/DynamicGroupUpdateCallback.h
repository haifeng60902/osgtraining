#ifndef _DYNAMIC_GROUP_UPDATE_CALLBACK_H_
#define _DYNAMIC_GROUP_UPDATE_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>


#include <vector>

class DynamicGroupUpdateCallback : public osg::NodeCallback
{
public:
	DynamicGroupUpdateCallback( std::vector< osg::ref_ptr< osg::Geode > > &_vecGeode );
	~DynamicGroupUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	std::vector< osg::ref_ptr< osg::Geode > > *m_vecGeode;

	int m_iCount;
	int m_iSign;
};

#endif	//_DYNAMIC_GROUP_UPDATE_CALLBACK_H_