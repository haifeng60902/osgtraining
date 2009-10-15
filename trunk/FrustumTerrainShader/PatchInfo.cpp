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