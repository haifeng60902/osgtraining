#ifndef _TREE_H_
#define _TREE_H_

#include "BranchXML.h"
#include "LightSource.h"
#include "BranchXMLWindCallback.h"

#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osg/Program>

class Tree : public osg::Referenced
{
public:
	Tree( float fNear , float fFar );
	~Tree();

	//������� ���� ���������� ������
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//���������������� �����
	void InitBranch( float fNear , float fFar );

	//���������������� �����
	void InitFronds( float fNear , float fFar );

	//���������������� ������
	void InitLeaf( float fNear , float fFar );

	//�������� ������ ��� ������ � �����
	void AddShaderBranch();

	//�������� ������ ��� ������ � �����
	void AddShaderLeaf();

	//��������� uniform'� ��� ������� ������
	void AddLeafUniforms();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//�������� uniform �������
	void AddUniformMatrix();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	//����, ���������� ��������� ������ � �����
	osg::ref_ptr< osg::Group > m_branchFrondsNode;

	//����, ���������� ��������� �����
	osg::ref_ptr< osg::Group > m_leafNode;

	//��������� ��������� �����
	osg::Uniform *m_LightPos;

	//�������� �����
	LightSource m_LightSource;

	//�������� ����� ����������
	BranchXMLWindCallback *m_BrClbk;
};

#endif	//_TREE_H_