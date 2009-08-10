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
	Tree();
	~Tree();

	//вернуть узел содержащий дерево
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициализировать ствол
	void InitBranch();

	//инициализировать ветки
	void InitFronds();

	//инициализировать листву
	void InitLeaf();

	//добавить шейдер для ствола в сцену
	void AddShaderBranch();

	//добавить шейдер для листвы в сцену
	void AddShaderLeaf();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//добавить uniform матрицы
	void AddUniformMatrix();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//узел, содержащий геометрию ствола и веток
	osg::ref_ptr< osg::Group > m_branchFrondsNode;

	//узел, содержащий геометрию веток
	osg::ref_ptr< osg::Group > m_leafNode;

	//положение источника света
	osg::Uniform *m_LightPos;

	//источник света
	LightSource m_LightSource;

	//обратный вызов обновления
	BranchXMLWindCallback *m_BrClbk;
};

#endif	//_TREE_H_