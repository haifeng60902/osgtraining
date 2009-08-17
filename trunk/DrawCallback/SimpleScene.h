#ifndef _SIMPLE_SCENE_H_
#define _SIMPLE_SCENE_H_

#include "DrawCallback.h"

#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osg/Program>
#include <osg/Image>

class SimpleScene : public osg::Referenced
{
public:
	SimpleScene();
	~SimpleScene();

	//������� ���� ���������� ���������
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//���������������� ���������
	void InitGeom();

	//�������� ��������
	void AddTexture();

	//�������� ������
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	std::vector< unsigned int > m_vIndex;

	osg::ref_ptr< osg::Uniform > m_Offset;

	osg::ref_ptr< osg::Geometry > m_Geom;

	//���������������� ���������
	DrawCallback *dCbk;
};

#endif	//_SIMPLE_SCENE_H_