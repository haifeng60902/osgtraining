#ifndef _DYNAMIC_GROUP_SIZE_H_
#define _DYNAMIC_GROUP_SIZE_H_

#include <osg/Group>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <vector>

class DynamicGroupSize : public osg::Referenced
{
public:
	DynamicGroupSize();
	~DynamicGroupSize();

	//������� ���� ���������� ���������
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//���������������� �������� ����
	void InitNode();
	
	//�������� ��������
	void AddTexture();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	std::vector< osg::ref_ptr< osg::Geode > > m_vecGeode;
};

#endif	//_DYNAMIC_GROUP_SIZE_H_