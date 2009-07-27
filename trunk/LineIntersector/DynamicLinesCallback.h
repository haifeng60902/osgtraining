#ifndef _DYNAMIC_LINES_CALLBACK_H_
#define _DYNAMIC_LINES_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Array>
#include <osg/Group>
#include <osg/PrimitiveSet>

#include <vector>

class DynamicLinesCallback : public osg::NodeCallback
{
public:
	DynamicLinesCallback();
	~DynamicLinesCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	//������������� ����, ����������� �����
	void InitPointsNode();
	
	//����� ������ �����
	osg::ref_ptr< osg::Group > GetLinesGroup( osg::Node* node );

	//������������ ���������� ��������� �����
	void DinamicUpdateLines();

	//����������� �������
	void ColisionDetection();

	//�������� ��������� �����
	float GetRand( float fScale );

	//����� ������ ������
	void FindVertexArray( osg::ref_ptr< osg::Group > group );

	//��������� ���� ������ ������������ �����
	void FillPointsNode( const std::vector< osg::Vec3d > &res );

	//���� ���������� ����� ����������� ��������� �������
	osg::ref_ptr< osg::Group > m_PointsGroup;

	//���������� ������ �����
	osg::ref_ptr< osg::Vec3Array > m_LinesVertexs;

	//������ ��� ��������� ����� � ������
	osg::ref_ptr< osg::Vec3Array > m_V;
	osg::ref_ptr< osg::Vec4Array > m_C;

	osg::ref_ptr< osg::DrawArrays > m_DA;

	osg::Node *m_pNode;
};

#endif	//_DYNAMIC_LINES_CALLBACK_H_