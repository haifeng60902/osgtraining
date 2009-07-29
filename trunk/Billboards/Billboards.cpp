#include "Billboards.h"

#include "constant.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/FileUtils>

Billboards::Billboards()
{
	//выделить пам€ть под корневую круппу
	m_rootGroup = new osg::Group;

	//формирование сцены
	buildScene();
}

Billboards::~Billboards()
{

}

void Billboards::buildScene()
{
	//формирование сцены

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
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );

	for ( int i = 0; i < NUM_QUADS ; ++i )
	{
		//формирование случайной позиции
		osg::Vec3 pos = osg::Vec3( GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) );

		//4 координаты дл€ osg::PrimitiveSet::QUADS
		v->push_back( pos + osg::Vec3( -MAX_SIZE , 0 , -MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( MAX_SIZE , 0 , -MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( MAX_SIZE , 0 , MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( -MAX_SIZE , 0 , MAX_SIZE ) );

		//одна нормаль,обща€ на весь полигон
		n->push_back( osg::Vec3( 0, -1 , 0 ) );
	
		//текстурные координаты
		tc->push_back( osg::Vec2( 0 , 0 ) );
		tc->push_back( osg::Vec2( 1 , 0 ) );
		tc->push_back( osg::Vec2( 1 , 1 ) );
		tc->push_back( osg::Vec2( 0 , 1 ) );

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

void Billboards::AddShader()
{
	//добавить шейдер в сцену
	osg::StateSet* ss = m_rootGroup->getOrCreateStateSet();

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/C3E1v.vert" );
	LoadShaderSource( FragObj , "glsl/C2E2f.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//создание параметра дл€ передачи в шейдер
	osg::Uniform *_color = new osg::Uniform("_ZZ3SconstantColor", osg::Vec3( 1.0f, 0.0f, 1.0f));

	//добавление в состо€ние сцены
	ss->addUniform( _color );

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
