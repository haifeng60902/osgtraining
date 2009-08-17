#include "DrawCallback.h"

DrawCallback::DrawCallback()
{
	setUseDisplayList( true );
}

DrawCallback::~DrawCallback()
{

}

int a = 0.0;
void DrawCallback::drawImplementation(osg::RenderInfo& renderInfo) const
{
	m_uOffset->set( osg::Vec3( a , 0 , 0 ) );
	glColor3f( 0,0,0 );

	_geometry->draw(renderInfo);

	if ( a % 2)
	{
		m_uOffset->set( osg::Vec3( 512.0f , 0 , 0 ) );
		glColor3f( 512.0,0,0 );
		_geometry->draw(renderInfo);
	}

	a += 1;
}

osg::BoundingBox DrawCallback::computeBound() const
{
	osg::BoundingBox bb;

	return bb;
}