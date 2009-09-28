#ifndef _DYNAMIC_GROUP_UPDATE_CALLBACK_H_
#define _DYNAMIC_GROUP_UPDATE_CALLBACK_H_

#include "VisiblePatchArray.h"
#include "DynamicGroupLevel0512Node.h"
#include "DynamicGroupLevel1024Node.h"
#include "DynamicGroupLevel2048Node.h"
#include "DynamicGroupLevel4096Node.h"
#include "DynamicGroupLevel8192Node.h"
#include "DynamicGroupLevel16384Node.h"
#include "DynamicGroupLevel32768Node.h"

#include <osg/NodeCallback>
#include <osg/Geode>

#include <map>

class DynamicGroupUpdateCallback : public osg::NodeCallback
{
public:
	DynamicGroupUpdateCallback( osg::ref_ptr< osg::Uniform > _unfVisPos );
	~DynamicGroupUpdateCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	//�������� ��������� ����������� ����������� �����
	void ResetChilds();

	//�������� �������������� �������� � �������� ����
	void AddChilds( osg::ref_ptr< osg::Group > group );

	//�������� ��������� ����������� ��� ���������� ������ �������
	void UpdateShaderPos();

	//�������� ����������
	void UpdateStatistic();

	//����� ����������� ������ ������� ������
	VisiblePatchArray m_VisiblePatchArray;

	//���� ���������� �� ������������ ������������ ������
	DynamicGroupLevel0512Node m_Node512;
	DynamicGroupLevel1024Node m_Node1024;
	DynamicGroupLevel2048Node m_Node2048;
	DynamicGroupLevel4096Node m_Node4096;
	DynamicGroupLevel8192Node m_Node8192;
	DynamicGroupLevel16384Node m_Node16384;
	DynamicGroupLevel32768Node m_Node32768;

	//uniform ��� ������� ��������� �����������
	osg::ref_ptr< osg::Uniform > m_unfVisPos;

	//����������
	std::map< int , int > m_Statistic;
};

#endif	//_DYNAMIC_GROUP_UPDATE_CALLBACK_H_