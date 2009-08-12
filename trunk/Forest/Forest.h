#ifndef _FOREST_H_
#define _FOREST_H_

#include "BranchXML.h"
#include "LightSource.h"
#include "BranchXMLWindCallback.h"

#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osg/Program>
#include <osg/Image>

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

	//�������� ������ ��� ������ � �����
	void AddShaderBranch();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//�������� uniform �������
	void AddUniformMatrix();

	//��������� uniform'� ��� ������� ������
	void AddLeafUniforms();

	//�������� ��������
	void AddTexture();

	//��������� ��������� �����
	osg::Uniform *m_LightPos;

	//�������� �����
	LightSource m_LightSource;

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	//�������� ����� ����������
	BranchXMLWindCallback *m_BrClbk;
};

#endif	//_FOREST_H_