#ifndef _DYNAMIC_HOUSE_UPDATE_CALLBACK_H_
#define _DYNAMIC_HOUSE_UPDATE_CALLBACK_H_

#include "../binData/binPatch.h"

#include <osg/NodeCallback>
#include <osg/Geode>

class DynamicHouseUpdateCallback : public osg::NodeCallback
{
public:
	DynamicHouseUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	//перебрать все содержимое патча и добавить его в m_mHause
	void ParsePatch( const binPatch &_binPatch , double dX , double dY );

	//здесь будет накапливаться информация о видимых домах
	tMapHouse m_mHause;
};

#endif	//_DYNAMIC_HOUSE_UPDATE_CALLBACK_H_