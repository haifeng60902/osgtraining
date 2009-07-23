#ifndef _DYNAMIC_LINES_H_
#define _DYNAMIC_LINES_H_ 

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Group>

class DynamicLines : public osg::Referenced
{
public:
	DynamicLines();
	~DynamicLines();

	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//������������ �������� ���� �������
	void InitRootNode();

	//�������� ��������� �����
	float GetRand( float fScale );

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_DYNAMIC_LINES_H_