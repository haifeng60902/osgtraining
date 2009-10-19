#ifndef _PATCH_INFO_H_
#define _PATCH_INFO_H_

#include "Singleton.h"
#include "binData/binPatch.h"
#include "binData/enumTypes.h"

#include <osg/Image>

#include <map>

class PatchInfo : public Singleton< PatchInfo >
{
public:
	PatchInfo();
	~PatchInfo();

	//инициализировать данные о содержимом патчей
	void InitPatchData();

	//преобразовать входные координаты угла патча в пару индексов
	void Convert( double dX , double dY , unsigned char *ucR , unsigned char *ucG );

	//вернуть ссылку на данные о содержимом патчей
	binPatch &GetBinPatch( unsigned char ucR , unsigned char ucG ){ return m_binPatch[ ucG ][ ucR ]; };

	//вернуть узел из кэша по его типу
	osg::ref_ptr< osg::Node > GetModel( eHouse _house );

private:
	typedef std::map< eHouse , osg::ref_ptr< osg::Node > > tMapModelCache;

	//тайлы сгрупированны 16 на 16
	binPatch m_binPatch[16][16];

	//изображение содержащие индексы
	osg::ref_ptr<osg::Image> m_ImageIndex;

	//кэшированные модели
	tMapModelCache m_ModelCache;
};

#endif	//_PATCH_INFO_H_