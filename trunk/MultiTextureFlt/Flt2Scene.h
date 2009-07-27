#ifndef _FLT_2SCENE_H_
#define _FLT_2SCENE_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Program>

class Flt2Scene : public osg::Referenced
{
public:
	Flt2Scene();
	~Flt2Scene();

	//������� ���� ����������� �����
	osg::ref_ptr< osg::Group > getRootNode() { return _rootNode.get(); }

private:
	//��������� ������
	void loadScene();

	//�������� ������ � �����
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	osg::ref_ptr<osg::Group> _rootNode;
};

#endif	//_FLT_2SCENE_H_