#ifndef _TERRAIN_SHADER_PATCH_NODE_H_
#define _TERRAIN_SHADER_PATCH_NODE_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Program>

class TerrainShaderPatchNode : public osg::Referenced
{
public:
	TerrainShaderPatchNode();
	virtual ~TerrainShaderPatchNode();

	//вернуть узел содержащий части земли
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициализировать корневой узел земли
	void InitTerrainNode();

	//добавить шейдер в узел
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_TERRAIN_SHADER_PATCH_NODE_H_