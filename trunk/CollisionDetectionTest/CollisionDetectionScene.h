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

	//������� ������ �� ������ � isecHAT
	tListIsecHAT &GetListIsecHAT(){ return m_lIsecHAT; };

private:
	//������������ �������� ���� �������
	void InitRootNode();

	//�������� ������ ������ �����������
	void AddModelTerrain();

	//�������� ������ ���������
	void AddModelMi17();

	//�������� isector
	void AddIsecHAT( osg::ref_ptr<osg::MatrixTransform> _mt );

	//�������� ��������� �����
	float GetRand( float fScale );

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	tListIsecHAT m_lIsecHAT;
};

#endif	//_COLLISION_DETECTION_SCENE_H_