#ifndef _DYNAMIC_LINES_CALLBACK_H_
#define _DYNAMIC_LINES_CALLBACK_H_

#include <osg/NodeCallback>

class DynamicLinesCallback : public osg::NodeCallback
{
public:
	DynamicLinesCallback();
	~DynamicLinesCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	//получить случайное число
	float GetRand( float fScale );
};

#endif	//_DYNAMIC_LINES_CALLBACK_H_