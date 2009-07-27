#ifndef _DYNAMIC_LINES_CALLBACK_H_
#define _DYNAMIC_LINES_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Array>
#include <osg/Group>
#include <osg/PrimitiveSet>

class DynamicLinesCallback : public osg::NodeCallback
{
public:
	DynamicLinesCallback();
	~DynamicLinesCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	//������������� ����, ����������� �����
	void InitPointsNode();
	
	//������������ ���������� ��������� �����
	void DinamicUpdateLines( osg::Node* node );

	//����������� �������
	void ColisionDetection( osg::Vec3Array* v , osg::Node* node );

	//�������� ��������� �����
	float GetRand( float fScale );

	//���� ���������� ����� ����������� ��������� �������
	osg::ref_ptr< osg::Group > m_PointsGroup;

	//������ ��� ��������� ����� � ������
	osg::ref_ptr< osg::Vec3Array > m_V;
	osg::ref_ptr< osg::Vec4Array > m_C;

	osg::ref_ptr< osg::DrawArrays > m_DA;
};

#endif	//_DYNAMIC_LINES_CALLBACK_H_