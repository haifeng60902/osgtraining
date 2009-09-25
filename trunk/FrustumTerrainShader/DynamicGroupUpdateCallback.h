#ifndef _DYNAMIC_GROUP_UPDATE_CALLBACK_H_
#define _DYNAMIC_GROUP_UPDATE_CALLBACK_H_

#include "VisiblePatchArray.h"

#include <osg/NodeCallback>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Image>

#include <map>

class DynamicGroupUpdateCallback : public osg::NodeCallback
{
public:
	DynamicGroupUpdateCallback();
	~DynamicGroupUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	//поиск максимального размера патча
	int FindMax();

	//обновить коэффициенты из файла
	void UpdateKof();

	//обновить статистику
	void UpdateStatistic();

	//класс формирующий массив видимых патчей
	VisiblePatchArray m_VisiblePatchArray;

	//изображение содержащие индексы
	osg::ref_ptr<osg::Image> m_ImageIndex;

	//масштаб и смещение
	double m_dAdd;
	double m_dScale;

	//статистика
	std::map< int , int > m_Statistic;
};

#endif	//_DYNAMIC_GROUP_UPDATE_CALLBACK_H_