#ifndef _FOREST_H_
#define _FOREST_H_

#include "BranchXML.h"

#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osg/Program>

class Forest : public osg::Referenced
{
public:
	Forest();
	~Forest();

	//������� ���� ���������� ���
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//���������������� ������
	void InitBranches();

	//���������������� ����� ����
	void InitFronds();

	//������ ��������� ����� uniform
	void SetPos( osg::StateSet *ss , float i , float j );

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_FOREST_H_