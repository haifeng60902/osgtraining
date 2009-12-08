#include "osgNodeLeaf.h"

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

osgNodeLeaf::osgNodeLeaf()
{

}

osgNodeLeaf::~osgNodeLeaf()
{

}

void osgNodeLeaf::LODSave()
{
	//сохранить листву по LOD'ам
	binLeaf &leaf = xmlTree::Instance().GetLeaf();

	//количество LOD'ов веток
	int numLOD = leaf.m_vLeaf.size();

	//сортировка по текстурам
	int iNumT = leaf.m_vTextures.size();
	for ( int i = 0 ; i < iNumT ; ++i )
	{
		for ( int j = 0 ; j < numLOD ; ++j )
		{
			osg::ref_ptr< osg::Group > nodeLeaf = new osg::Group;

			//инициировать корневой узел данными
			nodeLeaf->addChild( InitLeafGeode( i , j ).get() );

			//добавить текстуру
			AddTexture( nodeLeaf->getOrCreateStateSet() , i );

			std::stringstream ss;
			ss << "leaf_" << i << "_" << j;
			std::string sStl = ss.str() + ".stl";
			std::string sFlt = ss.str() + ".flt";
			std::string sObj = ss.str() + ".obj";

			bool resStl = osgDB::writeNodeFile( *nodeLeaf , sStl.c_str() );
			bool resFlt = osgDB::writeNodeFile( *nodeLeaf , sFlt.c_str() );
			bool resObj = osgDB::writeNodeFile( *nodeLeaf , sObj.c_str() );

			int a = 1;
		}
	}
}

osg::ref_ptr< osg::Geode > osgNodeLeaf::InitLeafGeode( int iTex , int iLOD )
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

	//получить ссылку на данные листвы
	binLeaf &leaf = xmlTree::Instance().GetLeaf();

	//копируем координаты
	for ( int i = 0 ; i < leaf.m_vLeaf[ iLOD ].m_vVerOffset.size() / 3 ; ++i )
	{
		//считать номер используемой текстуры
		int iNumT = leaf.m_vLeaf[ iLOD ].m_vVerOffset[ i * 3 + 2 ];
		
		if ( ( iTex * 2 ) == iNumT )
		{
			osg::Vec3 coord( leaf.m_vLeaf[ iLOD ].m_vVertex[ i * 3 ] + leaf.m_vLeaf[ iLOD ].m_vVerOffset[ i * 3 ] , 
				leaf.m_vLeaf[ iLOD ].m_vVertex[ i * 3 + 1 ] ,
				leaf.m_vLeaf[ iLOD ].m_vVertex[ i * 3 + 2 ] + leaf.m_vLeaf[ iLOD ].m_vVerOffset[ i * 3 + 1 ] );
			v->push_back( coord );

			osg::Vec3 normal( leaf.m_vLeaf[ iLOD ].m_vNormal[ i * 3 ] , 
				leaf.m_vLeaf[ iLOD ].m_vNormal[ i * 3 + 1 ] ,
				leaf.m_vLeaf[ iLOD ].m_vNormal[ i * 3 + 2 ] );
			n->push_back( normal );

			osg::Vec2 tex0( leaf.m_vLeaf[ iLOD ].m_vTexCoord[ i * 2 ] ,
				leaf.m_vLeaf[ iLOD ].m_vTexCoord[ i * 2 + 1 ] );
			tc->push_back( tex0 );
		}
		else
			if ( ( iTex * 2 + 1 ) == iNumT )
			{
				osg::Vec3 coord( leaf.m_vLeaf[ iLOD ].m_vVertex[ i * 3 ] - leaf.m_vLeaf[ iLOD ].m_vVerOffset[ i * 3 ] , 
					leaf.m_vLeaf[ iLOD ].m_vVertex[ i * 3 + 1 ] ,
					leaf.m_vLeaf[ iLOD ].m_vVertex[ i * 3 + 2 ] + leaf.m_vLeaf[ iLOD ].m_vVerOffset[ i * 3 + 1 ] );
				v->push_back( coord );

				osg::Vec3 normal( leaf.m_vLeaf[ iLOD ].m_vNormal[ i * 3 ] , 
					leaf.m_vLeaf[ iLOD ].m_vNormal[ i * 3 + 1 ] ,
					leaf.m_vLeaf[ iLOD ].m_vNormal[ i * 3 + 2 ] );
				n->push_back( normal );

				osg::Vec2 tex0( leaf.m_vLeaf[ iLOD ].m_vTexCoord[ i * 2 ] ,
					leaf.m_vLeaf[ iLOD ].m_vTexCoord[ i * 2 + 1 ] );
				tc->push_back( tex0 );
			}
	}

	geom->setVertexArray( v.get() );
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setTexCoordArray( 0, tc.get() );

	geom->addPrimitiveSet( new osg::DrawArrays(
		osg::PrimitiveSet::QUADS , 0 , tc->size() / 2 ) );

	geode->addDrawable( geom.get() );

	//настроить альфа канал
	SetupAlfaFunc( geode.get() , iLOD );

	return geode.get();
}

void osgNodeLeaf::SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD )
{
	//настроить альфа канал

	//получить ссылку на данные веток
	binLeaf &leaf = xmlTree::Instance().GetLeaf();

	if ( leaf.m_vLeaf[ iLOD ].m_fAlfa > 0.0f)
	{
		//настройка атрибутов состояния LOD ствола
		osg::StateSet* state = geode->getOrCreateStateSet();

		//помечаем объект как имеющий прозрачность
		state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

		// Turn on alpha testing
		osg::AlphaFunc* af = new osg::AlphaFunc(
			osg::AlphaFunc::GREATER, leaf.m_vLeaf[ iLOD ].m_fAlfa );
		state->setAttributeAndModes( af );
	}
}

void osgNodeLeaf::AddTexture( osg::StateSet* state , int i )
{
	//добавить текстуру

	//получить ссылку на данные листвы
	binLeaf &leaf = xmlTree::Instance().GetLeaf();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( leaf.m_vTextures[ i ].c_str() );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	tex0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	tex0->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP ); 
	tex0->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP ); 

	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() );

	//включаем отсечение нелицевых граней
	osg::CullFace* cf = new osg::CullFace( osg::CullFace::BACK );
	state->setAttributeAndModes( cf );
}