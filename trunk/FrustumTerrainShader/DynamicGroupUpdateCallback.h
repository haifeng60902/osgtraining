#ifndef _DYNAMIC_GROUP_UPDATE_CALLBACK_H_
#define _DYNAMIC_GROUP_UPDATE_CALLBACK_H_

#include "VisiblePatchArray.h"
#include "DynamicGroupLevel0512Node.h"
#include "DynamicGroupLevel1024Node.h"
#include "DynamicGroupLevel2048Node.h"

#include <osg/NodeCallback>
#include <osg/Geode>

#include <map>

class DynamicGroupUpdateCallback : public osg::NodeCallback
{
public:
	DynamicGroupUpdateCallback();
	~DynamicGroupUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	//�������� ��������� ����������� ����������� �����
	void ResetChilds();

	//�������� �������������� �������� � �������� ����
	void AddChilds( osg::ref_ptr< osg::Group > group );

	//����� ����������� ������ ������� ������
	VisiblePatchArray m_VisiblePatchArray;

	//���� ���������� �� ������������ ������������ ������
	DynamicGroupLevel0512Node m_Node512;
	DynamicGroupLevel1024Node m_Node1024;
	DynamicGroupLevel2048Node m_Node2048;
};

#endif	//_DYNAMIC_GROUP_UPDATE_CALLBACK_H_