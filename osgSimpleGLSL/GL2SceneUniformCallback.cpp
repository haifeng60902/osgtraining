#include "GL2SceneUniformCallback.h"

#include <iostream>

GL2SceneUniformCallback::GL2SceneUniformCallback()
{

}

GL2SceneUniformCallback::~GL2SceneUniformCallback()
{

}

void GL2SceneUniformCallback::operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
{
	static int i = 0;
	if ( i == 0)
		std::cout << "GL2SceneUniformCallback::operator()\n";
	i++;

	//задать случайный цвет
	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;

	uniform->set( osg::Vec3( r , g , b ) );

}
