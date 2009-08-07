#ifndef _BRANCH_XML_H_
#define _BRANCH_XML_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>

class BranchXML : public osg::Referenced
{
public:
	BranchXML();
	~BranchXML();

	osg::ref_ptr< osg::Geode > getBranchGeode() { return m_branchGeode.get(); }

private:
	//������������ �������� ���� �������
	void InitBranchGeode();

	//�������� ��������
	void AddTexture();

	//��������� ����� �����
	void SetupAlfaFunc();

	//�������� ���� ��������� ������
	osg::ref_ptr< osg::Geode > m_branchGeode;
};

#endif	//_BRANCH_XML_H_