#include "LightSourceCallback.h"

#include <osg/MatrixTransform>

LightSourceCallback::LightSourceCallback() : m_LightPos( NULL )
{

}

LightSourceCallback::~LightSourceCallback()
{

}

void LightSourceCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	osg::MatrixTransform *mt = dynamic_cast< osg::MatrixTransform* >( node );
	if ( mt )
	{
		static float x = 0.0f;
		osg::Matrix m;
		float dX = cos( x ) * 15.0f;
		float dY = -sin( x ) * 15.0f;

		m.makeTranslate( osg::Vec3( dX , dY , 10 ) );
		mt->setMatrix( m );

		if ( m_LightPos )
			m_LightPos->set( osg::Vec3( dX , dY , 10 ) );

		x += 0.01;
	}
}