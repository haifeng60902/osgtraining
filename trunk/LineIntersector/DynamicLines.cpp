#include "DynamicLines.h"

#include "DynamicLinesCallback.h"

#include "constant.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>

#include <iostream>

DynamicLines::DynamicLines()
{
	// the root of our scenegraph.
	m_rootNode = new osg::Group;

	//инициировать корневой узел данными
	InitRootNode();

	//добавить модель
	AddModel();

	//задать класс обратного вызова
	m_rootNode->setUpdateCallback( new DynamicLinesCallback );
}

DynamicLines::~DynamicLines()
{
	std::cout << "DynamicLines::~DynamicLines()\n";
}

void DynamicLines::InitRootNode()
{
	//инициировать корневой узел данными
	osg::ref_ptr< osg::Group > groupLines = new  osg::Group;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

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

	groupLines->addChild( geode.get() );

	//динамически меняемый узел
	groupLines->setDataVariance( osg::Object::DYNAMIC );

	// Disable lighting in the root node's StateSet. Make
	//   it PROTECTED to prevent osgviewer from enabling it.
	osg::StateSet* state = groupLines->getOrCreateStateSet();
	state->setMode( GL_LIGHTING,
		osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED );

	//назначить имя группе
	groupLines->setName( "groupLines" );

	m_rootNode->addChild( groupLines.get() );
}

void DynamicLines::AddModel()
{
	//добавить модель
	osg::ref_ptr<osg::Node> root = osgDB::readNodeFile( "Flt/mi17/MI_17_lod.flt" );

	m_rootNode->addChild( root.get() );
}

float DynamicLines::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;

}