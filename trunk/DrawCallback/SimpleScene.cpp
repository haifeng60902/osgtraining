#include "SimpleScene.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

SimpleScene::SimpleScene()
{
	dCbk = new DrawCallback();

	m_rootNode = new osg::Group;

	//инициализировать геометрию
	InitGeom();

	//добавить текстуру
	AddTexture();

	//добавить шейдер
	AddShader();

	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

SimpleScene::~SimpleScene()
{

}

void SimpleScene::InitGeom()
{
	// Create an object to store geometry in.
	m_Geom = new osg::Geometry;

	m_Geom->setUseDisplayList( false );

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	m_Geom->setVertexArray( v.get() );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	m_Geom->setTexCoordArray( 0, tc.get() );

//////////////////////////////////////////////////////////////////////////
	int sizeC=513;
	//Заполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
		for (int j = 0 ; j < sizeC ; ++j )
		{
			v->push_back( osg::Vec3( j - sizeC / 2.0, -2.4f , i - sizeC / 2.0 ) );
			tc->push_back( osg::Vec2( j / ( sizeC - 1.0 ) , i / ( sizeC - 1.0 )  ) );
		}

		m_vIndex.push_back( 0 );
		m_vIndex.push_back( sizeC );
		int count = sizeC - 1;
		int ind = 0;
		while( count > 0 )
		{
			for( int i = 0 ; i < count ; i++ )
			{
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] + 1 );
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] + 1 );
			}
			ind = m_vIndex.size() - 3;
			m_vIndex.push_back( m_vIndex[ ind ] );
			count--;

			for( int i = 0 ; i< count ; i++ )
			{
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] + sizeC );
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] + sizeC );
			}

			ind = m_vIndex.size() - 3;
			m_vIndex.push_back( m_vIndex[ ind ] );

			for( int i = 0 ; i < count ; i++ )
			{
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] - 1 );
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] - 1 );
			}

			ind = m_vIndex.size() - 3;
			m_vIndex.push_back( m_vIndex[ ind ] );
			count--;

			for( int i=0 ; i < count ; i++ )
			{
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] - sizeC );
				ind = m_vIndex.size() - 2;
				m_vIndex.push_back( m_vIndex[ ind ] - sizeC );
			}
			ind = m_vIndex.size() - 3;
			m_vIndex.push_back( m_vIndex[ ind ] );
		}
//////////////////////////////////////////////////////////////////////////

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	m_Geom->setNormalArray( n.get() );
	m_Geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );

	m_Geom->addPrimitiveSet( new osg::DrawElementsUInt(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size(), &m_vIndex[ 0 ] ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	//geode->addDrawable( m_Geom.get() );

//////////////////////////////////////////////////////////////////////////
	//передать геометрию для отрисовки
	dCbk->SetGeometry( m_Geom.get() );

	geode->addDrawable( dCbk );
//////////////////////////////////////////////////////////////////////////


	m_rootNode->addChild( geode );

	// Don't throw away single-vertex primitives.
	osg::BoundingBox bbox( -500, -500, -500, 500, 500, 500);
	geode->setInitialBound( bbox );
}

void SimpleScene::AddTexture()
{
	//добавить текстуру

	//добавить текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image>image0 = osgDB::readImageFile( "landcover9.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode( osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE );
	//state->setAttributeAndModes( polymode, osg::StateAttribute::ON );
}

void SimpleScene::AddShader()
{
	//добавить шейдер в сцену

	//формирование сцены с шейдером
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "simple_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/simple.vert" );
	LoadShaderSource( FragObj , "glsl/simple.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );

	//управляемое смещение
	m_Offset = new osg::Uniform( "offset" , osg::Vec3( 32 , 0 , 0) );
	ss->addUniform( m_Offset.get() );

//////////////////////////////////////////////////////////////////////////
	//передать uniform смещения
	dCbk->SetUniformOffset( m_Offset.get() );
}

void SimpleScene::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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
