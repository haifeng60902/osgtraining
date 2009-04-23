#include "GL2SceneCallback.h"

#include <osg/Group>
#include <osg/Uniform>

#include <iostream>
GL2SceneCallback::GL2SceneCallback()
{

}

GL2SceneCallback::~GL2SceneCallback()
{
	std::cout << "~GL2SceneCallback()\n";
}

void GL2SceneCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	static int i = 0;
	if ( i == 0)
		std::cout << "GL2SceneCallback::operator()\n";
	i++;

	osg::Group *group = dynamic_cast< osg::Group* >( node );
	if ( group )
	{
		//получить состояние узла
		osg::StateSet* ss = group->getOrCreateStateSet();

		//извлечь uniform
		osg::Uniform *_color = ss->getUniform( "_ZZ3SconstantColor" );

		if ( _color )
			//задать случайный цвет
			SetRandColor( _color );
	}
}

void GL2SceneCallback::SetRandColor( osg::Uniform *_color )
{
	//задать случайный цвет
	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;

	_color->set( osg::Vec3( r , g , b ) );
}