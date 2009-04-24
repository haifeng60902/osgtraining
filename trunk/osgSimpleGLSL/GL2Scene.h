#ifndef _GL_2_SCENE_H_
#define  _GL_2_SCENE_H_

#include <osg/Node>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <osg/Program>

class GL2Scene : public osg::Referenced
{
public:
	GL2Scene();

	osg::ref_ptr< osg::Group > getRootNode() { return _rootNode; }
	
protected:
	~GL2Scene();

private:	/*methods*/
	osg::ref_ptr<osg::Group> buildScene();

private:	/*data*/
	//добавить шейдер в сцену
	void AddShader();

	//добавить текстуру
	void AddTexture();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	osg::ref_ptr<osg::Group> _rootNode;
};

typedef osg::ref_ptr<GL2Scene> GL2ScenePtr;

#endif	//_GL_2_SCENE_H_