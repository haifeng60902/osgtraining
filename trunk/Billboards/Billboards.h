#ifndef _BILLBOARDS_H_
#define _BILLBOARDS_H_

#include <osg/Referenced>
#include <osg/Group>
#include <osg/ref_ptr>
#include <osg/Program>

class Billboards : public osg::Referenced
{
public:
	Billboards();
	~Billboards();

	//������� ��������� �� �������� ������
	osg::ref_ptr< osg::Group > getRootGroup() { return m_rootGroup.get(); }

private:
	//������������ �����
	void buildScene();

	//�������� ������ � �����
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//�������� ��������� �����
	float GetRand( float fScale );

	//�������� ������, ���������� ���������
	osg::ref_ptr< osg::Group > m_rootGroup;
};

#endif	//_BILLBOARDS_H_