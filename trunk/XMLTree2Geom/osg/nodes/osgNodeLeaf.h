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

	//��������� ������ �� LOD'��
	void LODSave();

private:
	//������������ �������� ���� �������
	osg::ref_ptr< osg::Geode > InitLeafGeode( int iTex , int iLOD );

	//��������� ����� �����
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//�������� ��������
	void AddTexture( osg::StateSet* state , int i );
};

#endif	//_OSG_NODE_LEAF_H_