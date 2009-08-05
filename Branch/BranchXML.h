#ifndef _BRANCH_XML_H_
#define _BRANCH_XML_H_

#include "LightSource.h"

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

	//добавить динамическую текстуру
	void AddDynamicTexture();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//узел трансформации
	osg::ref_ptr< osg::MatrixTransform > m_MatrNode;

	//источник света
	LightSource m_LightSource;

	//матрица трансформации ветра
	osg::Uniform *m_wRot;

	//изобрание, содержащее матрицы трансформации
	osg::ref_ptr<osg::Image> image0;
};

#endif	//_BRANCH_XML_H_