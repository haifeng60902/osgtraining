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

	//��������� ����� �� LOD'��
	void LODSave();

private:
	//������������ �������� ���� �������
	osg::ref_ptr< osg::Geode > InitFrondsGeode( int iLOD );

	//��������� ����� �����
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//�������� ��������
	void AddTexture( osg::StateSet* state );
};

#endif	//_OSG_NODE_FRONDS_H_