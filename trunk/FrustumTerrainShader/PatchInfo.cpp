#include "PatchInfo.h"

#include "binData/enumTypes.h"

#include <osgDB/ReadFile>

PatchInfo::PatchInfo()
{
	// загрузить изображение
	m_ImageIndex = osgDB::readImageFile( "index.bmp" );
}

PatchInfo::~PatchInfo()
{

}

void PatchInfo::InitPatchData()
{
	//инициализировать данные о содержимом патчей
	
	binHouse _house;
	_house.m_dX = 63.0 * 2.0;
	_house.m_dY = 512.0 - 169.0 * 2.0;
	m_binPatch[ 1 ][ 3 ].m_mapHouse[ SCHOOL_106 ].push_back( _house );

	m_ModelCache[ SCHOOL_106 ] = osgDB::readNodeFile( "06/255-106-0.flt" );

	// определение ограничивающего объема, размер земли 256км(в 1 км - 1024 метра), максимальная высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 256.0 * 1024.0 , 256.0 * 1024.0 , 64 );

	osg::Group* group = dynamic_cast< osg::Group* >( m_ModelCache[ SCHOOL_106 ].get() );

	if ( group )
	{
		//получить количество Drawable узлов
		unsigned int numDr = group->getNumChildren();

		osg::Group *node = dynamic_cast< osg::Group* >( group->getChild( 0 ) );
	
		//получить количество Drawable узлов
		unsigned int numDr1 = node->getNumChildren();

		osg::Geode *node1 = dynamic_cast< osg::Geode* >( node->getChild( 0 ) );
		
		osg::Geometry *mtDrawable = dynamic_cast< osg::Geometry* >( node1->getDrawable( 0 ) );
		mtDrawable->setInitialBound( bbox );

		int a = 1;

		//std::cout << "osg::Geode: " << mtGeode->getName() << "\n";
	}
}

void PatchInfo::Convert( double dX , double dY , unsigned char *ucR , unsigned char *ucG )
{
	//преобразовать входные координаты угла патча в пару индексов

	unsigned char *dataR = m_ImageIndex->data();

	int iIndX = dX / 262144.0 * 512.0;
	int iIndY = dY / 262144.0 * 512.0;

	( *ucR ) = dataR[ iIndY * 512 * 3 + iIndX * 3 ];
	( *ucG ) = dataR[ iIndY * 512 * 3 + iIndX * 3 + 1];
}

osg::ref_ptr< osg::Node > PatchInfo::GetModel( eHouse _house )
{
	//вернуть узел из кэша по его типу
	tMapModelCache::iterator it = m_ModelCache.find( _house );

	if ( it == m_ModelCache.end() )
	{
		return NULL;
	}

	//вернуть указатель
	return it->second.get();
}