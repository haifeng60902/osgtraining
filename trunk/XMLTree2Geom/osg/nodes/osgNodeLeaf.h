#ifndef _OSG_NODE_LEAF_H_
#define _OSG_NODE_LEAF_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>

class osgNodeLeaf
{
public:
	osgNodeLeaf();
	~osgNodeLeaf();

	//сохранить листву по LOD'ам
	void LODSave();

private:
	//инициировать корневой узел данными
	osg::ref_ptr< osg::Geode > InitLeafGeode( int iTex , int iLOD );

	//настроить альфа канал
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//добавить текстуру
	void AddTexture( osg::StateSet* state , int i );
};

#endif	//_OSG_NODE_LEAF_H_