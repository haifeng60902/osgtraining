#ifndef _FAKE_TREE_H_
#define _FAKE_TREE_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/MatrixTransform>

class FakeTree : public osg::Referenced
{
public:
	FakeTree( osg::Vec3 pos );
	~FakeTree();

	//������� ��������� �� �������� ������
	osg::ref_ptr< osg::MatrixTransform > getRootTransform() { return m_rootTransform.get(); }

private:
	//������������ ����� � ��������
	void buildSceneShader();

	//�������� ��������� �����
	float GetRand( float fScale );

	osg::ref_ptr< osg::MatrixTransform > m_rootTransform;
};

#endif	//_FAKE_TREE_H_