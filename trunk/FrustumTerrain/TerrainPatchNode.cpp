#include "TerrainPatchNode.h"

#include <osg/BoundingBox>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

TerrainPatchNode::TerrainPatchNode()
{
	m_rootNode = new osg::Group;

	//создать геметрию
	CreateGeometry();

	//инициализировать корневой узел земли
	InitTerrainNode();

	//создать текстуру, содержащую смещени€ геометрии
	CreateTexture();

	//добавить шейдер в узел
	AddShader();

	// определение ограничивающего объема, размер земли 1024км(в 1 км - 1024 метра), максимальна€ высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 500 );
	m_rootNode->setInitialBound( bbox );
}

TerrainPatchNode::~TerrainPatchNode()
{

}

void TerrainPatchNode::CreateGeometry()
{
	//создать геметрию

	//корневой узел геометрии
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

	for ( int y = 0 ; y < 32 ; ++y )
		for ( int x = 0 ; x < 32 ; ++x )
			//создать очередную геометрию
			geode->addDrawable( CreateGeometry( x , y ).get() );

	// определение ограничивающего объема, размер земли 1024км(в 1 км - 1024 метра), максимальна€ высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 500 );
	geode->setInitialBound( bbox );

	m_rootNode->addChild( geode.get() );
}

osg::ref_ptr< osg::Geometry > TerrainPatchNode::CreateGeometry( int x , int y )
{
	//создать очередную геометрию

	//Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

//////////////////////////////////////////////////////////////////////////
	//std::vector< unsigned int > *m_pIndex = new std::vector< unsigned int >;
	std::vector< unsigned int > m_vIndex;// = *m_pIndex;

	float rndOffset = GetFloatRand() * 128.0;

	int sizeC = 33;
	//«аполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
		for (int j = 0 ; j < sizeC ; ++j )
		{
			v->push_back( osg::Vec3( j * 32, i * 32, 0 ) );
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
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( x / 32.0 + 1.0 / 64.0 , y / 32.0 + 1.0 / 64.0  , 0.f ) );

	geom->setVertexArray( v.get() );
	geom->setNormalArray( n.get() );

	geom->addPrimitiveSet( new osg::DrawElementsUInt(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() , &m_vIndex[ 0 ] ) );

	// определение ограничивающего объема, размер земли 1024км(в 1 км - 1024 метра), максимальна€ высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 500 );
	geom->setInitialBound( bbox );

	return geom.get();
}

void TerrainPatchNode::InitTerrainNode()
{
	//инициализировать корневой узел земли

	//создать экземпл€р обратного вызова определени€ видимости
	m_rpPatchCullCallback = new PatchCullCallback;

	//обратный вызов определени€ видимости
	m_rootNode->setCullCallback( m_rpPatchCullCallback.get() );
}

void TerrainPatchNode::CreateTexture()
{
	//создать текстуру, содержащую смещени€ геометрии
	//добавить текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// динамически создать текстуру
	//текстура с координатами
	osg::ref_ptr<osg::Image> image = new osg::Image;

	//image->setImage( 64, 64, 1,
	//	GL_RGBA, GL_RGBA, GL_FLOAT,
	//	new unsigned char[ 4 * 4 * 64 * 64 ],
	//	osg::Image::USE_NEW_DELETE);
	image->allocateImage( 32, 32, 1, GL_RGBA, GL_FLOAT); 

	image->setInternalTextureFormat( GL_RGBA_FLOAT32_ATI );

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

	//передать динамически мен€емую картинку
	m_rpPatchCullCallback->SetDynamicImage( image.get() );
}

void TerrainPatchNode::AddShader()
{
	//добавить шейдер

	//формирование сцены с шейдером
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "terrain_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/terrain.vert" );
	LoadShaderSource( FragObj , "glsl/terrain.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов дл€ работы с текстурными модул€ми
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );
}

void TerrainPatchNode::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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

float TerrainPatchNode::GetFloatRand()
{
	return (float)rand() / (float)RAND_MAX;
}