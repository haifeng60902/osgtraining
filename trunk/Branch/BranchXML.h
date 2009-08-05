#ifndef _BRANCH_XML_H_
#define _BRANCH_XML_H_

#include "LightSource.h"

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/MatrixTransform>
#include <osg/Program>

class BranchXML : public osg::Referenced
{
public:
	BranchXML();
	~BranchXML();

	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//������������ �������� ���� �������
	void InitRootNode();

	//�������� ��������
	void AddTexture();

	//��������� ����� �����
	void SetupAlfaFunc();

	//������������ ����� � ��������
	void buildSceneShader();

	//�������� ������ � �����
	void AddShader( osg::StateSet* ss );

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//�������� ������������ ��������
	void AddDynamicTexture();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	//���� �������������
	osg::ref_ptr< osg::MatrixTransform > m_MatrNode;

	//�������� �����
	LightSource m_LightSource;

	//������� ������������� �����
	osg::Uniform *m_wRot;

	//���������, ���������� ������� �������������
	osg::ref_ptr<osg::Image> image0;
};

#endif	//_BRANCH_XML_H_