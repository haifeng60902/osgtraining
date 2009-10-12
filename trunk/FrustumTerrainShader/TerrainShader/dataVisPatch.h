#ifndef _DATA_VIS_PATCH_H_
#define _DATA_VIS_PATCH_H_

#include <osg/Geode>
#include <osg/Uniform>

#define DIST_SCALE 3.9f
#define GEOM_DIV 1

struct dataVisPatch
{
	dataVisPatch() : m_sOffset( "posOffset" )
		, m_sColorP( "colorP" )
		, m_sColorS( "colorS" )
		, m_sKofScale( "fKofScale" )
		, m_sDist( "dist" )
		, m_sTexCoordScale( "fTexCoordScale" )
		, m_sTexCoordAdd( "fTexCoordAdd" )
	{};

	//геометрия патча
	osg::ref_ptr< osg::Geode > m_Geode;

	//uniform для динамического смещения геометрии патча
	osg::ref_ptr< osg::Uniform > m_unfOffset;

	//uniform для задания основного цвета
	osg::ref_ptr< osg::Uniform > m_unfColorP;

	//uniform для задания вспомогательного цвета
	osg::ref_ptr< osg::Uniform > m_unfColorS;

	//uniform для задания коэффициента масштабирования
	osg::ref_ptr< osg::Uniform > m_unfKofScale;

	//uniform для задания расстояния
	osg::ref_ptr< osg::Uniform > m_unfDist;

	//uniform для для масштабирования текстурных координат
	osg::ref_ptr< osg::Uniform > m_unfTexCoordScale;

	//uniform для для для смещения текстурных координат
	osg::ref_ptr< osg::Uniform > m_unfTexCoordAdd;

	//имя переменной смещения
	std::string m_sOffset;

	//имя переменной основного цвета
	std::string m_sColorP;

	//имя переменной вспомогательного цвета
	std::string m_sColorS;

	//имя переменной для масштабирования координат
	std::string m_sKofScale;

	//имя переменной расстояния
	std::string m_sDist;

	//имя переменной для масштабирования текстурных координат
	std::string m_sTexCoordScale;

	//имя переменной для смещения текстурных координат
	std::string m_sTexCoordAdd;
};

#endif	//_DATA_VIS_PATCH_H_