#ifndef _TERRAIN_NODE_H_
#define _TERRAIN_NODE_H_

#include "TerrainShader/TerrainShaderPatchNode.h"
#include "BuildingShader/BuildingShaderPatchNode.h"

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

	//инициализировать корневой узел строений
	void InitBuildingNode();

	//добавить текстуру с картой высот
	void AddTextureHeightmap();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//класс отвечающий за формирование и отображение земной поверхности
	osg::ref_ptr< TerrainShaderPatchNode > m_TerrainShaderPatchNode;

	//класс отвечающий за формирование и отображение домов
	osg::ref_ptr< BuildingShaderPatchNode > m_BuildingShaderPatchNode;
};

#endif	//_TERRAIN_NODE_H_