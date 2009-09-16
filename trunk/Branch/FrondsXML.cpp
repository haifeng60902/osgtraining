#include "FrondsXML.h"

#include "xmlRoot/xmlRoot.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/AlphaFunc>
#include <osg/CullFace>

FrondsXML::FrondsXML( float fNear , float fFar ) : m_fNear( fNear )
	, m_fFar( fFar )
{
	//создать узел LOD
	m_FrondsLOD = new osg::LOD;

	//создать LOD'ы веток
	CreateFrondsLOD();

	//добавить текстуру
	AddTexture();
}

FrondsXML::~FrondsXML()
{

}

void FrondsXML::CreateFrondsLOD()
{
	//создать LOD'ы веток

	//получить ссылку на данные веток
	dataFronds &_data = xmlRoot::Instance().GetDataFronds();

	//количество LOD'ов ствола
	int numLOD = _data.m_vFrLOD.size();

	for ( int i = 0 ; i < numLOD ; ++i )
	{
		float fLODNear = 0.0f;
		float fLODFar = 0.0f;

		//расчет новых значений видимости LOD'ов
		CalcNewLODDist( i , numLOD
			, m_fNear , m_fFar , &fLODNear , &fLODFar );

		//инициировать корневой узел данными
		m_FrondsLOD->addChild( InitFrondsGeode( i ).get() 
			, fLODNear , fLODFar);
	}
}

osg::ref_ptr< osg::Geode > FrondsXML::InitFrondsGeode( int iLOD )
{
	//инициировать корневой узел данными

	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

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
	dataFronds &_data = xmlRoot::Instance().GetDataFronds();

	//копируем координаты
	for ( int i = 0 ; i < _data.m_vFrLOD[ iLOD ].m_vCoords.size() / 3 ; ++i )
	{
		osg::Vec3 coord( _data.m_vFrLOD[ iLOD ].m_vCoords[ i * 3 ] , 
			_data.m_vFrLOD[ iLOD ].m_vCoords[ i * 3 + 1 ] ,
			_data.m_vFrLOD[ iLOD ].m_vCoords[ i * 3 + 2 ] );
		v->push_back( coord );

		osg::Vec3 normal( _data.m_vFrLOD[ iLOD ].m_vNormals[ i * 3 ] , 
			_data.m_vFrLOD[ iLOD ].m_vNormals[ i * 3 + 1 ] ,
			_data.m_vFrLOD[ iLOD ].m_vNormals[ i * 3 + 2 ] );
		n->push_back( normal );

		osg::Vec4 tex0( _data.m_vFrLOD[ iLOD ].m_vTexCoords0[ i * 4 ] ,
			_data.m_vFrLOD[ iLOD ].m_vTexCoords0[ i * 4 + 1 ] ,
			_data.m_vFrLOD[ iLOD ].m_vTexCoords0[ i * 4 + 2 ] ,
			_data.m_vFrLOD[ iLOD ].m_vTexCoords0[ i * 4 + 3 ] );
		tc->push_back( tex0 );
	}

	geom->setVertexArray( v.get() );
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0 ; i < _data.m_vFrLOD[ iLOD ].m_Strips.size() ; ++i )
	{
		geom->addPrimitiveSet( new osg::DrawElementsUShort(
			osg::PrimitiveSet::TRIANGLE_STRIP, _data.m_vFrLOD[ iLOD ].m_Strips[ i ].size() ,
			&_data.m_vFrLOD[ iLOD ].m_Strips[ i ][ 0 ] ) );
	}

	geode->addDrawable( geom.get() );

	//настроить альфа канал
	SetupAlfaFunc( geode.get() , iLOD );

	return geode.get();
}

void FrondsXML::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_FrondsLOD->getOrCreateStateSet();

	//получить ссылку на данные веток
	dataFronds &_data = xmlRoot::Instance().GetDataFronds();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( _data.m_vTextures[0].c_str() );

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
	//osg::CullFace* cf = new osg::CullFace( osg::CullFace::FRONT );
	//state->setAttributeAndModes( cf );
}

void FrondsXML::SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD )
{
	//настроить альфа канал

	//получить ссылку на данные веток
	dataFronds &_data = xmlRoot::Instance().GetDataFronds();

	if ( _data.m_vFrLOD[ iLOD ].m_fAlphaTestValue > 0.0f)
	{
		//настройка атрибутов состояния LOD ствола
		osg::StateSet* state = geode->getOrCreateStateSet();

		//помечаем объект как имеющий прозрачность
		state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

		// Turn on alpha testing
		osg::AlphaFunc* af = new osg::AlphaFunc(
			osg::AlphaFunc::GREATER, _data.m_vFrLOD[ iLOD ].m_fAlphaTestValue );
		state->setAttributeAndModes( af );
	}
}

void FrondsXML::CalcNewLODDist( float i , float fSize
							   , float fNear , float fFar , float *fLODNear , float *fLODFar )
{
	//расчет новых значений видимости LOD'ов
	if ( i == 0 )
	{
		( *fLODNear ) = 0.0f;
		( *fLODFar ) = fNear;
	}
	else
	{
		float fStep = ( fFar - fNear ) / ( fSize - 1.0f );
		( *fLODNear ) = fNear + fStep * ( i - 1.0f );
		( *fLODFar ) = fNear + fStep * i;
	}
}