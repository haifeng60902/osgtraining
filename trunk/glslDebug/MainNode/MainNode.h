#ifndef _MAIN_NODE_H_
#define _MAIN_NODE_H_

#include <osg/ref_ptr>
#include <osg/Group>

class osg::Group;

class MainNode : public osg::Referenced
{
public:
	MainNode();
	~MainNode();

	//������������� ������
	void Init();

	//������� ������� ����
	osg::ref_ptr< osg::Group > GetNode(){ return m_Group.get(); };

private:
	//�������� ����
	osg::ref_ptr< osg::Group > m_Group;
};

#endif	//_MAIN_NODE_H_