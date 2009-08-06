#ifndef _BRANCH_XML_H_
#define _BRANCH_XML_H_

#include "LightSource.h"
#include "BranchXMLWindCallback.h"

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/MatrixTransform>
#include <osg/Program>

class BranchXML : public osg::Referenced
{
public:
	BranchXML();
	~BranchXML();

	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициировать корневой узел данными
	void InitRootNode();

	//добавить текстуру
	void AddTexture();

	//настроить альфа канал
	void SetupAlfaFunc();

	//формирование сцены с шейдером
	void buildSceneShader();

	//добавить шейдер в сцену
	void AddShader( osg::StateSet* ss );

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//добавить uniform матрицы
	void AddUniformMatrix();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//узел трансформации
	osg::ref_ptr< osg::MatrixTransform > m_MatrNode;

	//источник света
	LightSource m_LightSource;
	
	//обратный вызов обновления
	BranchXMLWindCallback *m_BrClbk;
};

#endif	//_BRANCH_XML_H_