#ifndef _GL_2_SCENE_CALLBACK_H_
#define _GL_2_SCENE_CALLBACK_H_

#include <osg/NodeCallback>

class osg::Uniform;

class GL2SceneCallback : public osg::NodeCallback
{
public:
	GL2SceneCallback();
	~GL2SceneCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	//задать случайный цвет
	void SetRandColor( osg::Uniform *_color );
};

#endif	//_GL_2_SCENE_CALLBACK_H_