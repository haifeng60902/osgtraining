#include "Forest.h"

#include "BranchXML.h"
//#include "FrondsXML.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

Forest::Forest()
{
	m_rootNode = new osg::Group;

	//инициализировать стволы
	InitBranches();

	//добавить шейдер для ствола в сцену
	AddShaderBranch();

	//добавить узел света
	m_rootNode->addChild( m_LightSource.getRootNode().get() );

	//класс обновления матриц ветра
	m_BrClbk = new BranchXMLWindCallback;
	m_rootNode->setUpdateCallback( m_BrClbk );

	//добавить uniform матрицы
	AddUniformMatrix();

	//настроить uniform'ы для шейдера листвы
	AddLeafUniforms();

	//добавить текстуру
	AddTexture();
}

Forest::~Forest()
{

}

void Forest::InitBranches()
{
	//инициализировать стволы

	//инициализировать ствол
	osg::ref_ptr< BranchXML > branch = new BranchXML;

	for ( int i = 0 ; i < 1 ; ++i )
		for ( int j = 0 ; j < 1 ; ++j )
		{
			//создать узел, содержащий ствол
			osg::ref_ptr< osg::Group > tree = new osg::Group;

			osg::StateSet *ss = tree->getOrCreateStateSet();

			//добавить геометрию ствола в узел
			tree->addChild( branch->getBranchGeode().get() );

			//добавить узел с геометрией ствола и смещением в общий лес
			m_rootNode->addChild( tree.get() );
		}
}

void Forest::AddShaderBranch()
{
	//добавить шейдер для ствола в сцену

	//формирование сцены с шейдером
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "branch_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/branch.vert" );
	LoadShaderSource( FragObj , "glsl/branch.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );

	//динамическое положение источника света
	m_LightPos = new osg::Uniform( "lightPos" , osg::Vec3(0,0,0) );

	ss->addUniform( m_LightPos );

	//передать Uniform положения источника света
	m_LightSource.SetUniform( m_LightPos );
}

void Forest::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
{
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

void Forest::AddUniformMatrix()
{
	//добавить uniform матрицы

	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	osg::Matrix m;

	std::vector< osg::Uniform* > vU;

	vU.push_back( new osg::Uniform( "wRot0" , m ) );
	ss->addUniform( vU.back() );
	vU.push_back( new osg::Uniform( "wRot1" , m ) );
	ss->addUniform( vU.back() );
	vU.push_back( new osg::Uniform( "wRot2" , m ) );
	ss->addUniform( vU.back() );
	vU.push_back( new osg::Uniform( "wRot3" , m ) );
	ss->addUniform( vU.back() );

	//передать вектор uniform матриц
	m_BrClbk->SetUniformMatrix( vU );
}

void Forest::AddLeafUniforms()
{
	//задать управление силой ветра
	//настроить uniform'ы для шейдера листвы
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	osg::Uniform *wind = new osg::Uniform( "windStrength" , 1.0f );
	ss->addUniform( wind );
	m_BrClbk->SetUniformWindStrength( wind  );
}

void Forest::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// динамически создать текстуру
	//текстура с координатами деревьев
	osg::ref_ptr<osg::Image> image = new osg::Image;

	image->setImage( 64, 64, 1,
		GL_RGBA, GL_RGBA, GL_FLOAT,
		new unsigned char[ 4 * 4 * 64 * 64 ],
		osg::Image::USE_NEW_DELETE);

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
	tex->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST);
	tex->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP); 
	tex->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP); 

	tex->setImage( image.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 1.
	state->setTextureAttributeAndModes( 1, tex.get() , osg::StateAttribute::ON );

	//передать динамически меняемую картинку
	m_BrClbk->SetDynamicImage( image.get() );
}