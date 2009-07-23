#include "DynamicLines.h"

#include "DynamicLinesCallback.h"

#include "constant.h"

#include <osg/Geometry>
#include <osg/Geode>

#include <iostream>

DynamicLines::DynamicLines()
{
	//инициировать корневой узел данными
	InitRootNode();
}

DynamicLines::~DynamicLines()
{
	std::cout << "DynamicLines::~DynamicLines()\n";
}

void DynamicLines::InitRootNode()
{
	//инициировать корневой узел данными

	// the root of our scenegraph.
	m_rootNode = new osg::Group;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Don't throw away single-vertex primitives.
	osg::BoundingBox bbox( -.1f, -.1f, -.1f, .1f, .1f, .1f );
	geom->setInitialBound( bbox );

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE );

	for ( int i = 0 ; i < NUM_LINES ; ++i )
	{
		//добавляем пару вершин со случайными координатами
		v->push_back( osg::Vec3( GetRand( MAX_SIZE ), GetRand( MAX_SIZE ), GetRand( MAX_SIZE ) ) );
		v->push_back( osg::Vec3( GetRand( MAX_SIZE ), GetRand( MAX_SIZE ), GetRand( MAX_SIZE ) ) );

		//цвет общий на примитив
		c->push_back( osg::Vec4( GetRand( 1.0 ), GetRand( 1.0 ), GetRand( 1.0 ) , 1.0 ) );
	}

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, 0, NUM_LINES * 2 ) );

	geom->setUseDisplayList( false );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	m_rootNode->addChild( geode.get() );

	//динамически меняемый узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );

	// Disable lighting in the root node's StateSet. Make
	//   it PROTECTED to prevent osgviewer from enabling it.
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();
	state->setMode( GL_LIGHTING,
		osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED );

	//задать класс обратного вызова
	m_rootNode->setUpdateCallback( new DynamicLinesCallback );	
}

float DynamicLines::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale;

}