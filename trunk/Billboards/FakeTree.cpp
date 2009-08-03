#include "FakeTree.h"

#include "constant.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/FileUtils>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osg/AlphaFunc>

FakeTree::FakeTree( osg::Vec3 pos )
{
	m_rootTransform = new osg::MatrixTransform;

	//формирование сцены с шейдером
	buildSceneShader();

	osg::Matrix m;
	m.makeTranslate( pos );
	m_rootTransform->setMatrix( m );

	//статический узел
	m_rootTransform->setDataVariance( osg::Object::STATIC );
}

FakeTree::~FakeTree()
{

}

void FakeTree::buildSceneShader()
{
	//формирование сцены с шейдером

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0; i < NUM_QUADS ; ++i )
	{
		//формирование случайной позиции
		osg::Vec3 pos = osg::Vec3( GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) + ALT_OFFSET );

		//4 координаты для osg::PrimitiveSet::QUADS
		v->push_back( pos );
		v->push_back( pos );
		v->push_back( pos );
		v->push_back( pos );

		//одна нормаль,общая на весь полигон
		n->push_back( osg::Vec3( 0, -1 , 0 ) );

		//текстурные координаты
		tc->push_back( osg::Vec4( 0 , 0 , -MAX_SIZE , -MAX_SIZE ) );
		tc->push_back( osg::Vec4( 1 , 0 , MAX_SIZE , -MAX_SIZE ) );
		tc->push_back( osg::Vec4( 1 , 1 , MAX_SIZE , MAX_SIZE ) );
		tc->push_back( osg::Vec4( 0 , 1 , -MAX_SIZE , MAX_SIZE ) );
	}

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, v->size() ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

	geode->addDrawable( geom.get() );

	m_rootTransform->addChild( geode.get() );
}

float FakeTree::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;
}