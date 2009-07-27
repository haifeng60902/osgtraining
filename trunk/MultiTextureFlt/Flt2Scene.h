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

	//вернуть узел загруженной сцены
	osg::ref_ptr< osg::Group > getRootNode() { return _rootNode.get(); }

private:
	//загрузить модель
	void loadScene();

	//добавить шейдер в сцену
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	osg::ref_ptr<osg::Group> _rootNode;
};

#endif	//_FLT_2SCENE_H_