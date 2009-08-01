#ifndef _BILLBOARDS_H_
#define _BILLBOARDS_H_

#include "LightSource.h"

#include <osg/Referenced>
#include <osg/Group>
#include <osg/ref_ptr>
#include <osg/Program>
#include <osg/Texture2D>

class Billboards : public osg::Referenced
{
public:
	Billboards();
	~Billboards();

	//вернуть указатель на корневую группу
	osg::ref_ptr< osg::Group > getRootGroup() { return m_rootGroup.get(); }

private:
	//загрузить текстуру
	void LoadTexture();

	//формирование сцены с шейдером
	void buildSceneShader();

	//формирование сцены
	void buildScene();

	//добавить плоскость
	void AddPlane();

	//настройка состо€ни€
	void SetupStateSet( osg::StateSet* ss );

	//добавить шейдер в сцену
	void AddShader( osg::StateSet* ss );

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//получить случайное число
	float GetRand( float fScale );

	//корнева€ группа, содержаща€ геометрию
	osg::ref_ptr< osg::Group > m_rootGroup;

	//обща€ текстура
	osg::ref_ptr<osg::Texture2D> m_Tex0;

	//источник света
	LightSource m_LightSource;
};

#endif	//_BILLBOARDS_H_