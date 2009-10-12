#ifndef _BUILDING_SHADER_PATCH_NODE_H_
#define _BUILDING_SHADER_PATCH_NODE_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Program>

class BuildingShaderPatchNode : public osg::Referenced
{
public:
	BuildingShaderPatchNode();
	virtual ~BuildingShaderPatchNode();

	//вернуть узел содержащий застройку
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициализировать корневой узел застройки
	void InitBuildingNode();

	//добавить шейдер в узел
	void AddShader();

	//настроить uniform'ы
	void SetupUniforms( osg::StateSet* ss );

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//uniform для задания положения наблюдателя
	osg::ref_ptr< osg::Uniform > m_unfVisPos;

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_BUILDING_SHADER_PATCH_NODE_H_