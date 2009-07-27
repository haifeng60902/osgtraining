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
	
	//динамическое обновление положения линий
	void DinamicUpdateLines( osg::Node* node );

	//определение колизий
	void ColisionDetection();

	//получить случайное число
	float GetRand( float fScale );
};

#endif	//_DYNAMIC_LINES_CALLBACK_H_