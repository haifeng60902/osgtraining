#ifndef _COLLISION_DETECTION_SCENE_H_
#define _COLLISION_DETECTION_SCENE_H_

#include "osgIsectorHAT.h"

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Group>

#include <list>

class CollisionDetectionScene : public osg::Referenced
{
public:
	typedef std::list< osg::ref_ptr< osgIsectorHAT > > tListIsecHAT;

	CollisionDetectionScene();

	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

	//вернуть ссылку на список с isecHAT
	tListIsecHAT &GetListIsecHAT(){ return m_lIsecHAT; };

private:
	//инициировать корневой узел данными
	void InitRootNode();

	//добавить модель земной поверхности
	void AddModelTerrain();

	//добавить модель вертолета
	void AddModelMi17();

	//добавить isector
	void AddIsecHAT( osg::ref_ptr<osg::MatrixTransform> _mt );

	//получить случайное число
	float GetRand( float fScale );

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	tListIsecHAT m_lIsecHAT;
};

#endif	//_COLLISION_DETECTION_SCENE_H_