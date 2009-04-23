#ifndef _GL_2_SCENE_UNIFORM_CALLBACK_H_
#define _GL_2_SCENE_UNIFORM_CALLBACK_H_

#include <osg/Uniform>

class GL2SceneUniformCallback : public osg::Uniform::Callback
{
public:
	GL2SceneUniformCallback();
	~GL2SceneUniformCallback();

	virtual void operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv );
};

#endif	//_GL_2_SCENE_UNIFORM_CALLBACK_H_