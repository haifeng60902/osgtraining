#ifndef _TERRAIN_NODE_H_
#define _TERRAIN_NODE_H_

#include "TerrainShader/TerrainShaderPatchNode.h"

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>

class TerrainNode : public osg::Referenced
{
public:
	TerrainNode();
	virtual ~TerrainNode();

	//вернуть узел содержащий землю
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//инициализировать корневой узел земли
	void InitTerrainNode();

	//добавить текстуру с картой высот
	void AddTextureHeightmap();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//класс отвечающий за формирование и вывод земной поверхности
	osg::ref_ptr< TerrainShaderPatchNode > m_TerrainShaderPatchNode;
};

#endif	//_TERRAIN_NODE_H_