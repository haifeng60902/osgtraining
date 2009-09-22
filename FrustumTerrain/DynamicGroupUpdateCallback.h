#ifndef _DYNAMIC_GROUP_UPDATE_CALLBACK_H_
#define _DYNAMIC_GROUP_UPDATE_CALLBACK_H_

#include "VisiblePatchArray.h"

#include <osg/NodeCallback>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Image>

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
	
	//класс формирующий массив видимых патчей
	VisiblePatchArray m_VisiblePatchArray;

	//изображение содержащие индексы
	osg::ref_ptr<osg::Image> m_ImageIndex;

	//масштаб и смещение
	double m_dAdd;
	double m_dScale;
};

#endif	//_DYNAMIC_GROUP_UPDATE_CALLBACK_H_