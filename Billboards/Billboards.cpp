#include "Billboards.h"

#include "constant.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/FileUtils>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osg/AlphaFunc>

Billboards::Billboards()
{
	//выделить пам€ть под корневую круппу
	m_rootGroup = new osg::Group;

	//загрузить текстуру
	LoadTexture();

	srand( 1 );

	//формирование сцены с шейдером
	buildSceneShader();

	srand( 1 );

	//формирование сцены
	//buildScene();

	//добавить плоскость
	AddPlane();
}

Billboards::~Billboards()
{

}

void Billboards::LoadTexture()
{
	//загрузить текстуру

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( "pic/AmericanElmLeaves_RT_1.tga" );

	// Attach the image in a Texture2D object
	m_Tex0 = new osg::Texture2D;
	m_Tex0->setImage( image0.get() );

	//освободить ресурсы, занимаемые изображением в RAM
	m_Tex0->setUnRefImageDataAfterApply( true );
}

void Billboards::buildSceneShader()
{
	//формирование сцены с шейдером

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0; i < NUM_QUADS ; ++i )
	{
		//формирование случайной позиции
		osg::Vec3 pos = osg::Vec3( GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) , 0 );

		//4 координаты дл€ osg::PrimitiveSet::QUADS
		v->push_back( pos );
		v->push_back( pos );
		v->push_back( pos );
		v->push_back( pos );

		//одна нормаль,обща€ на весь полигон
		n->push_back( osg::Vec3( 0, -1 , 0 ) );
	
		//текстурные координаты
		tc->push_back( osg::Vec4( 0 , 0 , -MAX_SIZE , -MAX_SIZE ) );
		tc->push_back( osg::Vec4( 1 , 0 , MAX_SIZE , -MAX_SIZE ) );
		tc->push_back( osg::Vec4( 1 , 1 , MAX_SIZE , MAX_SIZE ) );
		tc->push_back( osg::Vec4( 0 , 1 , -MAX_SIZE , MAX_SIZE ) );
	}
	
	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, v->size() ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

	osg::StateSet* ss = geode->getOrCreateStateSet();
	
	//настройка состо€ни€
	SetupStateSet( ss );

	geode->addDrawable( geom.get() );

	m_rootGroup->addChild( geode.get() );
}

void Billboards::SetupStateSet( osg::StateSet* ss )
{
	//настройка состо€ни€

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	ss->setTextureAttributeAndModes( 0, m_Tex0.get() , osg::StateAttribute::ON );

	//добавить шейдер в сцену
	AddShader( ss );

	//помечаем объект как имеющий прозрачность
	ss->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

	// Turn on alpha testing
	osg::AlphaFunc* af = new osg::AlphaFunc(
		osg::AlphaFunc::GREATER, 0.34 );
	
	ss->setAttributeAndModes( af );
}

void Billboards::buildScene()
{
	//формирование сцены с шейдером

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0; i < NUM_QUADS ; ++i )
	{
		//формирование случайной позиции
		osg::Vec3 pos = osg::Vec3( GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) , 0 );

		//4 координаты дл€ osg::PrimitiveSet::QUADS
		v->push_back( pos + osg::Vec3( -MAX_SIZE , 0 , -MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( MAX_SIZE , 0 , -MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( MAX_SIZE , 0 , MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( -MAX_SIZE , 0 , MAX_SIZE ) );

		//одна нормаль,обща€ на весь полигон
		n->push_back( osg::Vec3( 0, -1 , 0 ) );

		//текстурные координаты
		tc->push_back( osg::Vec4( 0 , 0 , -MAX_SIZE , -MAX_SIZE ) );
		tc->push_back( osg::Vec4( 1 , 0 , MAX_SIZE , -MAX_SIZE ) );
		tc->push_back( osg::Vec4( 1 , 1 , MAX_SIZE , MAX_SIZE ) );
		tc->push_back( osg::Vec4( 0 , 1 , -MAX_SIZE , MAX_SIZE ) );
	}

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, v->size() ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

	geode->addDrawable( geom.get() );

	m_rootGroup->addChild( geode.get() );
}

float Billboards::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;
}

void Billboards::AddShader( osg::StateSet* ss )
{
	//добавить шейдер в сцену

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/billboard.vert" );
	LoadShaderSource( FragObj , "glsl/billboard.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов дл€ работы с текстурными модул€ми
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
}  

void Billboards::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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

void Billboards::AddPlane()
{
	//добавить плоскость

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE );

	//4 координаты дл€ osg::PrimitiveSet::QUADS
	v->push_back( osg::Vec3( -MAX_VOLUME * 0.5 , -MAX_VOLUME * 0.5, -MAX_SIZE ) );
	v->push_back( osg::Vec3( MAX_VOLUME * 0.5, -MAX_VOLUME * 0.5, -MAX_SIZE ) );
	v->push_back( osg::Vec3( MAX_VOLUME * 0.5, MAX_VOLUME * 0.5,- MAX_SIZE ) );
	v->push_back( osg::Vec3( -MAX_VOLUME * 0.5, MAX_VOLUME * 0.5, -MAX_SIZE ) );

	//одна нормаль,обща€ на весь полигон
	n->push_back( osg::Vec3( 0, -1 , 0 ) );

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

	geode->addDrawable( geom.get() );

	m_rootGroup->addChild( geode.get() );
}