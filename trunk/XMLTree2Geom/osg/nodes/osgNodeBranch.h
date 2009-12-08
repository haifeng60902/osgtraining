#ifndef _OSG_NODE_BRANCH_H_
#define _OSG_NODE_BRANCH_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>
#include <osg/lod>

class osgNodeBranch
{
public:
	osgNodeBranch();
	~osgNodeBranch();

	//сохранить ствол по LOD'ам
	void LODSave();

private:
	//инициировать корневой узел данными
	osg::ref_ptr< osg::Geode > InitBranchGeode( int iLOD );

	//настроить альфа канал
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//добавить текстуру
	void AddTexture( osg::StateSet* state );
};

#endif	//_OSG_NODE_BRANCH_H_