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

	//вернуть узел содержащий лес
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициализировать стволы
	void InitBranches();

	//добавить шейдер для ствола в сцену
	void AddShaderBranch();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//добавить uniform матрицы
	void AddUniformMatrix();

	//настроить uniform'ы для шейдера листвы
	void AddLeafUniforms();

	//добавить текстуру
	void AddTexture();

	//положение источника света
	osg::Uniform *m_LightPos;

	//источник света
	LightSource m_LightSource;

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//обратный вызов обновления
	BranchXMLWindCallback *m_BrClbk;
};

#endif	//_FOREST_H_