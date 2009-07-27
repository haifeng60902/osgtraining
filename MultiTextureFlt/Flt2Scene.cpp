#include "Flt2Scene.h"

#include <osgDB/FileUtils>
#include <osgDB/ReadFile>

Flt2Scene::Flt2Scene()
{
	//загрузить модель
	loadScene();

	//добавить шейдер в сцену
	AddShader();
}

Flt2Scene::~Flt2Scene()
{

}

void Flt2Scene::loadScene()
{
	//загрузить модель

	//выдел€ем пам€ть
	_rootNode = new osg::Group;

	//добавить модель в сцену
	_rootNode->addChild( osgDB::readNodeFile( "flt/platest.flt" ) );
}

void Flt2Scene::AddShader()
{
	//добавить шейдер в сцену

	osg::StateSet* ss = _rootNode->getOrCreateStateSet();

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/simple.vert" );
	LoadShaderSource( FragObj , "glsl/simple.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//создание параметра дл€ передачи в шейдер
	osg::Uniform *_color = new osg::Uniform( "_ZZ3SconstantColor" , osg::Vec3( 1.0f, 0.0f, 1.0f));

	//задание callback'a дл€ динамического изменени€ параметра
	//_color->setUpdateCallback( new GL2SceneUniformCallback );

	//добавление в состо€ние сцены
	ss->addUniform( _color );

	//добавление uniform'ов дл€ работы с текстурными модул€ми
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );
	ss->addUniform( new osg::Uniform( "u_texture2" , 2 ) );
	ss->addUniform( new osg::Uniform( "u_texture3" , 3 ) );
}

void Flt2Scene::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
{
	// load source from a file.
	// load source from a file.
	std::string fqFileName = osgDB::findDataFile(fileName);

	if( fqFileName.length() != 0 )
	{
		shader->loadShaderSourceFromFile( fqFileName.c_str() );
	}
	else
	{
		osg::notify(osg::WARN) << "File \"" << fileName << "\" not found." << std::endl;
	}
}
