#include "Mi17UpdClbk.h"

#include <osg/MatrixTransform>

#include <iostream>

Mi17UpdClbk::Mi17UpdClbk() : m_dAngle( 0.0 )
, m_dAdd( 0.001 )
{

}

void Mi17UpdClbk::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	osg::MatrixTransform *mt = dynamic_cast< osg::MatrixTransform * >( node );

	if ( mt )
	{
		osg::Matrix tr;
		tr.makeTranslate( osg::Vec3( cos( m_dAngle ) * 100.0f
			, sin( m_dAngle ) * 100.0f
			, 100.f ) );
		mt->setMatrix( tr );

		//увеличиваем счетчик
		m_dAngle += m_dAdd;
	}

	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);  
}