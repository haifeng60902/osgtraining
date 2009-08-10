#include "LeafXML.h"

#include "xmlRoot/xmlRoot.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/AlphaFunc>
#include <osg/CullFace>

LeafXML::LeafXML()
{
	// the root of our scenegraph.
	m_leafGeode = new osg::Geode;

	//инициировать корневой узел данными
	InitLeafGeode();

	//добавить текстуры
	AddTextures();

	//настроить альфа канал
	SetupAlfaFunc();
}

LeafXML::~LeafXML()
{

}

void LeafXML::InitLeafGeode()
{
	//инициировать корневой узел данными

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

	// Create an array of normals.
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;

	// Create a Vec4Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec4Array> tc0 = new osg::Vec4Array;

	// Create a Vec3Array of texture coordinates for texture unit 1
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec3Array> tc1 = new osg::Vec3Array;

	//получить ссылку на данные листвы
	dataLeaf &_data = xmlRoot::Instance().GetDataLeaf();

	//копируем координаты
	for ( int i = 0 ; i < _data.m_vCoords.size() / 3 ; ++i )
	{
		osg::Vec3 coord( _data.m_vCoords[ i * 3 ] , 
			_data.m_vCoords[ i * 3 + 1 ] ,
			_data.m_vCoords[ i * 3 + 2 ] );
		v->push_back( coord );

		osg::Vec3 normal( _data.m_vNormals[ i * 3 ] , 
			_data.m_vNormals[ i * 3 + 1 ] ,
			_data.m_vNormals[ i * 3 + 2 ] );
		n->push_back( normal );

		osg::Vec4 tex0( _data.m_vTexCoords0[ i * 4 ] ,
			_data.m_vTexCoords0[ i * 4 + 1 ] ,
			_data.m_vTexCoords0[ i * 4 + 2 ] ,
			_data.m_vTexCoords0[ i * 4 + 3 ] );
		tc0->push_back( tex0 );

		osg::Vec3 tex1( _data.m_vTexCoords1[ i * 3 ] ,
			_data.m_vTexCoords1[ i * 3 + 1 ] ,
			_data.m_vTexCoords1[ i * 3 + 2 ] );
		tc1->push_back( tex1 );
	}

	geom->setVertexArray( v.get() );
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setTexCoordArray( 0, tc0.get() );
	geom->setTexCoordArray( 1, tc1.get() );

	geom->addPrimitiveSet( new osg::DrawArrays(
		osg::PrimitiveSet::QUADS , 0 , _data.m_vTexCoords0.size() / 4 ) );

	m_leafGeode->addDrawable( geom.get() );
}

void LeafXML::AddTextures()
{
	//добавить текстуры
	osg::StateSet* state = m_leafGeode->getOrCreateStateSet();

	//получить ссылку на данные веток
	dataLeaf &_data = xmlRoot::Instance().GetDataLeaf();

	for ( int i = 0 ; i < _data.m_vTextures.size() ; ++i )
	{
		// Load the texture image
		osg::ref_ptr<osg::Image> image = osgDB::readImageFile( _data.m_vTextures[ i ].c_str() );

		// Attach the image in a Texture2D object
		osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
		tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
		tex->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
		tex->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT); 
		tex->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT); 

		tex->setImage( image.get() );

		//освободить память от image
		tex->setUnRefImageDataAfterApply( true );

		// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
		// both on texture unit 0.
		state->setTextureAttributeAndModes( i , tex.get() );

	}

	//включаем отсечение нелицевых граней
	//osg::CullFace* cf = new osg::CullFace( osg::CullFace::BACK );
	//state->setAttributeAndModes( cf );
}

void LeafXML::SetupAlfaFunc()
{
	//настроить альфа канал

	//получить ссылку на данные листвы
	dataLeaf &_data = xmlRoot::Instance().GetDataLeaf();

	if ( _data.m_fAlphaTestValue > 0.0f)
	{
		//настройка атрибутов состояния LOD ствола
		osg::StateSet* state = m_leafGeode->getOrCreateStateSet();

		//помечаем объект как имеющий прозрачность
		state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

		// Turn on alpha testing
		osg::AlphaFunc* af = new osg::AlphaFunc(
			osg::AlphaFunc::GREATER, _data.m_fAlphaTestValue );
		state->setAttributeAndModes( af );
	}
}