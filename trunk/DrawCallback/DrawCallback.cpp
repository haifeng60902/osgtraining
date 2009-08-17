#include "DrawCallback.h"

DrawCallback::DrawCallback()
{

}

DrawCallback::~DrawCallback()
{

}

int a = 0.0;
void DrawCallback::drawImplementation( osg::RenderInfo& renderInfo , const osg::Drawable* drawable ) const
{
	m_uOffset->set( osg::Vec3( a , 0 , 0 ) );
	//glColor3f( 0,0,0 );

	drawable->drawImplementation(renderInfo);

//	if ( a % 2)
	{
		//m_uOffset->set( osg::Vec3( 512.0f , 0 , 0 ) );
		//glColor3f( 512.0,0,0 );
	//	 drawable->drawImplementation(renderInfo);
	}

	a += 1;
}