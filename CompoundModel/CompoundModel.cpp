#include "CompoundModel.h"

#include "TransGeomNode2VertArray.h"

#include <osgDB/ReadFile>
#include <osg/Texture2D>

#define NUM_COPY 128

CompoundModel::CompoundModel()
{
	//создать главный узел
	m_rootNode = new osg::Group;

	//инициализировать корневой узел
	InitNode();

	//добавить текстуру
	AddTexture();
}

CompoundModel::~CompoundModel()
{

}

void CompoundModel::InitNode()
{
//инициализировать корневой узел
	//загрузить модель
	//flt_optimize/09/255-109-0.flt
	//Flt/mi17/MI_17_lod.flt
	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile( "flt_optimize/09/255-109-0.flt" );

	//класс для извлечения данных геометрии
	osg::ref_ptr< TransGeomNode2VertArray > converter = new TransGeomNode2VertArray;

	//реорганизовать геометрию к треугольникам
	converter->apply( *model.get() );

	//создание из 1 модели нескольких копий
	CreateBigModel( converter->GetVertex() 
		, converter->GetNormals()
		, converter->GetTexCoord0() );

	//m_rootNode->addChild( model.get() );
}

void CompoundModel::CreateBigModel( const osg::Vec3Array *_v 
										 , const osg::Vec3Array *_n
										 , const osg::Vec2Array *_tc0 )
{
	//создание из 1 модели нескольких копий

	osg::ref_ptr< osg::Node > node = new osg::Node;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

//////////////////////////////////////////////////////////////////////////
	for ( int j = 0 ; j < NUM_COPY ; ++j )
		for ( int i = 0 ; i < _v->size() ; ++i )
		{
			v->push_back( osg::Vec3( _v->at( i ).x(), _v->at( i ).y() + j * 20.0, _v->at( i ).z() ) );
		}
//////////////////////////////////////////////////////////////////////////

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setNormalArray( n.get() );

//////////////////////////////////////////////////////////////////////////
	for ( int j = 0 ; j < NUM_COPY ; ++j )
		for ( int i = 0 ; i < _n->size() ; ++i )
			n->push_back( _n->at( i ) );
//////////////////////////////////////////////////////////////////////////

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );

//////////////////////////////////////////////////////////////////////////
	for ( int j = 0 ; j < NUM_COPY ; ++j )
		for ( int i = 0 ; i < _tc0->size() ; ++i )
			tc->push_back( _tc0->at( i ) );
//////////////////////////////////////////////////////////////////////////

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLES, 0, v->size() ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	m_rootNode->addChild( geode.get() );
}

void CompoundModel::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image>image0 = osgDB::readImageFile( "VillageTmplHouses.png" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );
}