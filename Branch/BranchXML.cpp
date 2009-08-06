#include "BranchXML.h"

#include "BranchXMLCallback.h"
#include "xmlRoot/xmlRoot.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/AlphaFunc>
#include <osg/CullFace>

BranchXML::BranchXML() : m_BrClbk( NULL )
{
	// the root of our scenegraph.
	m_rootNode = new osg::Group;

	m_MatrNode = new osg::MatrixTransform;

	//добавить 
	m_rootNode->addChild( m_MatrNode );

	//инициировать корневой узел данными
	InitRootNode();

	//добавить текстуру
	AddTexture();

	//настроить альфа канал
	SetupAlfaFunc();

	//формирование сцены с шейдером
	buildSceneShader();

	//динамически меняемый узел
	m_MatrNode->setDataVariance( osg::Object::DYNAMIC );

	//класс обновления матриц ветра
	m_BrClbk = new BranchXMLWindCallback;
	m_MatrNode->setUpdateCallback( m_BrClbk );

	//добавить uniform матрицы
	AddUniformMatrix();

	//передать узел света
	m_rootNode->addChild( m_LightSource.getRootNode().get() );
}

BranchXML::~BranchXML()
{

}

void BranchXML::InitRootNode()
{
	//инициировать корневой узел данными

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

	// Create an array of normals.
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;

	//получить ссылку на данные веток
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	//копируем координаты
	for ( int i = 0 ; i < _data.m_vCoords.size() / 3 ; ++i )
	{
		osg::Vec3 coord( _data.m_vCoords[ i * 3 ] , 
			_data.m_vCoords[ i * 3 + 1 ] ,
			_data.m_vCoords[ i * 3 + 2 ] );
		v->push_back( coord );

		osg::Vec3 normal( _data.m_vNormals[ i * 3 ] , 
			_data.m_vNormals[ i * 3 + 1 ] ,
			_data.m_vNormals[ i * 3 + 2 ] );
		n->push_back( normal );

		osg::Vec4 tex0( _data.m_vTexCoords0[ i * 4 ] ,
			_data.m_vTexCoords0[ i * 4 + 1 ] ,
			_data.m_vTexCoords0[ i * 4 + 2 ] ,
			_data.m_vTexCoords0[ i * 4 + 3 ] );
		tc->push_back( tex0 );
	}

	geom->setVertexArray( v.get() );
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0 ; i < _data.m_Strips.size() ; ++i )
	{
		geom->addPrimitiveSet( new osg::DrawElementsUShort(
			osg::PrimitiveSet::TRIANGLE_STRIP, _data.m_Strips[ i ].size() , &_data.m_Strips[ i ][ 0 ] ) );
	}

	geom->setUseDisplayList( false );

	//настроить очередной LOD
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	//geode->setUpdateCallback( new BranchXMLCallback );

	m_MatrNode->addChild( geode.get() );
}

void BranchXML::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_MatrNode->getOrCreateStateSet();

	//получить ссылку на данные веток
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( _data.m_sTexture.c_str() );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	tex0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	tex0->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT); 
	tex0->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT); 

	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() );

	//включаем отсечение нелицевых граней
	osg::CullFace* cf = new osg::CullFace( osg::CullFace::BACK );
	state->setAttributeAndModes( cf );
}

void BranchXML::SetupAlfaFunc()
{
	//настроить альфа канал

	//получить ссылку на данные веток
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	if ( _data.m_fAlphaTestValue > 0.0f)
	{
		//настройка атрибутов состояния LOD ствола
		osg::StateSet* state = m_MatrNode->getOrCreateStateSet();

		//помечаем объект как имеющий прозрачность
		state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

		// Turn on alpha testing
		osg::AlphaFunc* af = new osg::AlphaFunc(
			osg::AlphaFunc::GREATER, _data.m_fAlphaTestValue );
		state->setAttributeAndModes( af );
	}
}

void BranchXML::buildSceneShader()
{
	//формирование сцены с шейдером
	osg::StateSet* state = m_MatrNode->getOrCreateStateSet();

	//добавить шейдер в сцену
	AddShader( state );
}

void BranchXML::AddShader( osg::StateSet* ss )
{
	//добавить шейдер в сцену

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/branch.vert" );
	LoadShaderSource( FragObj , "glsl/branch.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );


	//динамическое положение источника света
	osg::Uniform *lightPos = new osg::Uniform( "lightPos" , osg::Vec3(0,0,0) );

	ss->addUniform( lightPos );

	//передать Uniform
	m_LightSource.SetUniform( lightPos );
}  

void BranchXML::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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

void BranchXML::AddUniformMatrix()
{
	//добавить uniform матрицы

	osg::StateSet* ss = m_MatrNode->getOrCreateStateSet();

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