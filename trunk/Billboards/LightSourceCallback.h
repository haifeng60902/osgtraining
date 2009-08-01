#ifndef _LIGHT_SOURCE_CALLBACK_H_
#define _LIGHT_SOURCE_CALLBACK_H_

#include <osg/NodeCallback>

class LightSourceCallback : public osg::NodeCallback
{
public:
	LightSourceCallback();
	~LightSourceCallback();

	//передать Uniform
	void SetUniform( osg::Uniform *_LightPos ){ m_LightPos = _LightPos; };

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	//положение источника света
	osg::Uniform *m_LightPos;

};
#endif	//_LIGHT_SOURCE_CALLBACK_H_