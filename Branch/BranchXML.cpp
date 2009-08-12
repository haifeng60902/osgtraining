#include "BranchXML.h"

#include "BranchXMLCallback.h"
#include "xmlRoot/xmlRoot.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/AlphaFunc>
#include <osg/CullFace>

BranchXML::BranchXML()
{
	// the root of our scenegraph.
	m_branchGeode = new osg::Geode;

	//инициировать корневой узел данными
	InitBranchGeode();

	//добавить текстуру
	AddTexture();

	//настроить альфа канал
	SetupAlfaFunc();
}

BranchXML::~BranchXML()
{

}

void BranchXML::InitBranchGeode()
{
	//инициировать корневой узел данными

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

	// Create an array of normals.
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;

	//получить ссылку на данные веток
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

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
		tc->push_back( tex0 );
	}

	geom->setVertexArray( v.get() );
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0 ; i < _data.m_Strips.size() ; ++i )
	{
		geom->addPrimitiveSet( new osg::DrawElementsUShort(
			osg::PrimitiveSet::TRIANGLE_STRIP, _data.m_Strips[ i ].size() , &_data.m_Strips[ i ][ 0 ] ) );
	}

	//geom->setUseDisplayList( false );

	m_branchGeode->addDrawable( geom.get() );
}

void BranchXML::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_branchGeode->getOrCreateStateSet();

	//получить ссылку на данные веток
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( _data.m_sTexture.c_str() );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	tex0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	tex0->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT); 
	tex0->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT); 

	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() );

	//включаем отсечение нелицевых граней
	osg::CullFace* cf = new osg::CullFace( osg::CullFace::BACK );
	state->setAttributeAndModes( cf );
}

void BranchXML::SetupAlfaFunc()
{
	//настроить альфа канал

	//получить ссылку на данные ствола
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	if ( _data.m_fAlphaTestValue > 0.0f)
	{
		//настройка атрибутов состояния LOD ствола
		osg::StateSet* state = m_branchGeode->getOrCreateStateSet();

		//помечаем объект как имеющий прозрачность
		state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

		// Turn on alpha testing
		osg::AlphaFunc* af = new osg::AlphaFunc(
			osg::AlphaFunc::GREATER, _data.m_fAlphaTestValue );
		state->setAttributeAndModes( af );
	}
}