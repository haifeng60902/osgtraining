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

BranchXML::BranchXML()
{
	// the root of our scenegraph.
	m_rootNode = new osg::Group;

	//инициировать корневой узел данными
	InitRootNode();

	//добавить текстуру
	AddTexture();

	//настроить альфа канал
	//SetupAlfaFunc();

	//динамически меняемый узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

BranchXML::~BranchXML()
{

}

void BranchXML::InitRootNode()
{
	//инициировать корневой узел данными

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec4Array> v = new osg::Vec4Array;
	geom->setVertexArray( v.get() );

	// Create an array of four normals.
	osg::ref_ptr<osg::Vec4Array> n = new osg::Vec4Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );

	//получить ссылку на данные веток
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	//копируем координаты
	for ( int i = 0 ; i < _data.m_vCoords.size() / 4 ; ++i )
	{
		osg::Vec4 coord( _data.m_vCoords[ i * 4 ] , 
			_data.m_vCoords[ i * 4 + 1 ] ,
			_data.m_vCoords[ i * 4 + 2 ] ,
			1 ); //_data.m_vCoords[ i * 4 + 3 ] );
		v->push_back( coord );

		osg::Vec4 normal( _data.m_vNormals[ i * 4 ] , 
			_data.m_vNormals[ i * 4 + 1 ] ,
			_data.m_vNormals[ i * 4 + 2 ] ,
			1 ); //_data.m_vNormals[ i * 4 + 3 ] );
		n->push_back( normal );

		osg::Vec2 tex0( _data.m_vTexCoords0[ i * 2 ] ,
			_data.m_vTexCoords0[ i * 2 + 1 ] );
		tc->push_back( tex0 );
	}

	for ( int i = 0 ; i < _data.m_Strips.size() ; ++i )
	{
		geom->addPrimitiveSet( new osg::DrawElementsUShort(
			osg::PrimitiveSet::TRIANGLE_STRIP, _data.m_Strips[ i ].size() , &_data.m_Strips[ i ][ 0 ] ) );
	}

	geom->setUseDisplayList( false );

	//настроить очередной LOD
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	geode->setUpdateCallback( new BranchXMLCallback );

	m_rootNode->addChild( geode.get() );
}

void BranchXML::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

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
}

void BranchXML::SetupAlfaFunc()
{
	//настроить альфа канал

	//настройка атрибутов состояния LOD ствола
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	//помечаем объект как имеющий прозрачность
	state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

	//получить ссылку на данные веток
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	// Turn on alpha testing
	osg::AlphaFunc* af = new osg::AlphaFunc(
		osg::AlphaFunc::GREATER, _data.m_fAlphaTestValue );
	state->setAttributeAndModes( af );
}