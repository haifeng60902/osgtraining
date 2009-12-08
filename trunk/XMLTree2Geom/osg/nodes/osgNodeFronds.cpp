#include "osgNodeFronds.h"

#include "xmlTree.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/Image>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/AlphaFunc>
#include <osg/CullFace>
#include <osg/Node>
#include <osg/Group>
#include <osg/Drawable>

#include <sstream>

osgNodeFronds::osgNodeFronds()
{

}

osgNodeFronds::~osgNodeFronds()
{

}

void osgNodeFronds::LODSave()
{
	//сохранить ветки по LOD'ам
	binFronds &fronds = xmlTree::Instance().GetFronds();

	//количество LOD'ов веток
	int numLOD = fronds.m_vFronds.size();

	for ( int i = 0 ; i < numLOD ; ++i )
	{
		osg::ref_ptr< osg::Group > nodeFronds = new osg::Group;

		//инициировать корневой узел данными
		nodeFronds->addChild( InitFrondsGeode( i ).get() );

		//добавить текстуру
		AddTexture( nodeFronds->getOrCreateStateSet() );

		std::stringstream ss;
		ss << "fronds" << i;
		std::string sStl = ss.str() + ".stl";
		std::string sFlt = ss.str() + ".flt";
		std::string sObj = ss.str() + ".obj";
	
		bool resStl = osgDB::writeNodeFile( *nodeFronds , sStl.c_str() );
		bool resFlt = osgDB::writeNodeFile( *nodeFronds , sFlt.c_str() );
		bool resObj = osgDB::writeNodeFile( *nodeFronds , sObj.c_str() );

		int a = 1;
	}
}

osg::ref_ptr< osg::Geode > osgNodeFronds::InitFrondsGeode( int iLOD )
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
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;

	//получить ссылку на данные веток
	binFronds &fronds = xmlTree::Instance().GetFronds();

	//копируем координаты
	for ( int i = 0 ; i < fronds.m_vFronds[ iLOD ].m_vVertex.size() / 3 ; ++i )
	{
		osg::Vec3 coord( fronds.m_vFronds[ iLOD ].m_vVertex[ i * 3 ] , 
			fronds.m_vFronds[ iLOD ].m_vVertex[ i * 3 + 1 ] ,
			fronds.m_vFronds[ iLOD ].m_vVertex[ i * 3 + 2 ] );
		v->push_back( coord );

		osg::Vec3 normal( fronds.m_vFronds[ iLOD ].m_vNormal[ i * 3 ] , 
			fronds.m_vFronds[ iLOD ].m_vNormal[ i * 3 + 1 ] ,
			fronds.m_vFronds[ iLOD ].m_vNormal[ i * 3 + 2 ] );
		n->push_back( normal );

		osg::Vec2 tex0( fronds.m_vFronds[ iLOD ].m_vTexCoord[ i * 2 ] ,
			fronds.m_vFronds[ iLOD ].m_vTexCoord[ i * 2 + 1 ] );
		tc->push_back( tex0 );
	}

	geom->setVertexArray( v.get() );
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0 ; i < fronds.m_vFronds[ iLOD ].m_vvIndex.size() ; ++i )
	{
		geom->addPrimitiveSet( new osg::DrawElementsUShort(
			osg::PrimitiveSet::TRIANGLE_STRIP, fronds.m_vFronds[ iLOD ].m_vvIndex[ i ].size() , &fronds.m_vFronds[ iLOD ].m_vvIndex[ i ][ 0 ] ) );
	}

	geode->addDrawable( geom.get() );

	//настроить альфа канал
	SetupAlfaFunc( geode.get() , iLOD );

	return geode.get();
}

void osgNodeFronds::SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD )
{
	//настроить альфа канал

	//получить ссылку на данные веток
	binFronds &fronds = xmlTree::Instance().GetFronds();

	if ( fronds.m_vFronds[ iLOD ].m_fAlfa > 0.0f)
	{
		//настройка атрибутов состояния LOD ствола
		osg::StateSet* state = geode->getOrCreateStateSet();

		//помечаем объект как имеющий прозрачность
		state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

		// Turn on alpha testing
		osg::AlphaFunc* af = new osg::AlphaFunc(
			osg::AlphaFunc::GREATER, fronds.m_vFronds[ iLOD ].m_fAlfa );
		state->setAttributeAndModes( af );
	}
}

void osgNodeFronds::AddTexture( osg::StateSet* state )
{
	//добавить текстуру

	//получить ссылку на данные веток
	binFronds &fronds = xmlTree::Instance().GetFronds();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( fronds.m_sTexture.c_str() );

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