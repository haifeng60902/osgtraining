#ifndef _OSG_NODE_FRONDS_H_
#define _OSG_NODE_FRONDS_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>
#include <osg/lod>

class osgNodeFronds
{
public:
	osgNodeFronds();
	~osgNodeFronds();

	//сохранить ветки по LOD'ам
	void LODSave();

private:
	//инициировать корневой узел данными
	osg::ref_ptr< osg::Geode > InitFrondsGeode( int iLOD );

	//настроить альфа канал
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//добавить текстуру
	void AddTexture( osg::StateSet* state );
};

#endif	//_OSG_NODE_FRONDS_H_