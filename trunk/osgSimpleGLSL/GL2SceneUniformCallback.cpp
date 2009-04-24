#include "GL2SceneUniformCallback.h"

#include <iostream>

GL2SceneUniformCallback::GL2SceneUniformCallback() : m_fLoop( 0.0f )
{

}

GL2SceneUniformCallback::~GL2SceneUniformCallback()
{

}

void GL2SceneUniformCallback::operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
{
	//задать случайный цвет
	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;
	
	//изменяем переменню
	static float fSign = 1.0f;
	m_fLoop = m_fLoop + 0.007 * fSign;

	if ( m_fLoop < 0.0)
	{
		fSign *= -1.0;
		m_fLoop = 0.0;
	}
	else
		if ( m_fLoop > 1.0 )
		{
			fSign *= -1.0;
			m_fLoop = 1.0;
		}

	uniform->set( osg::Vec3( m_fLoop , m_fLoop , m_fLoop ) );
}
