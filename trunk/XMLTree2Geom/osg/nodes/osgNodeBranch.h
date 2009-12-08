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

	//��������� ����� �� LOD'��
	void LODSave();

private:
	//������������ �������� ���� �������
	osg::ref_ptr< osg::Geode > InitBranchGeode( int iLOD );

	//��������� ����� �����
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//�������� ��������
	void AddTexture( osg::StateSet* state );
};

#endif	//_OSG_NODE_BRANCH_H_