#ifndef _DYNAMIC_HOUSE_UPDATE_CALLBACK_H_
#define _DYNAMIC_HOUSE_UPDATE_CALLBACK_H_

#include "../binData/binPatch.h"
#include "SimplyShaderHause.h"

#include <osg/NodeCallback>
#include <osg/Geode>

#include <vector>

class DynamicHouseUpdateCallback : public osg::NodeCallback
{
public:
	DynamicHouseUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	//перебрать все содержимое патча и добавить его в m_mHause
	void ParsePatch( const binPatch &_binPatch , double dX , double dY );

	//очистить данные с предыдущего шага
	void ClearPrevStep();

	//заполнить вектор
	void FillVector();

	//здесь будет накапливаться информация о видимых домах
	tMapHouse m_mHause;

	//вектор отображаемых домов
	std::vector< osg::ref_ptr< SimplyShaderHause > > m_vHouse;
	osg::Group *m_pGroup;

};

#endif	//_DYNAMIC_HOUSE_UPDATE_CALLBACK_H_