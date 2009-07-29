#include "Billboards.h"

#include "constant.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/FileUtils>

Billboards::Billboards()
{
	//�������� ������ ��� �������� ������
	m_rootGroup = new osg::Group;

	//������������ �����
	buildScene();

#ifdef USE_SHADER
	//�������� ������ � �����
	AddShader();
#endif
}

Billboards::~Billboards()
{

}

void Billboards::buildScene()
{
	//������������ �����

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
		//������������ ��������� �������
		osg::Vec3 pos = osg::Vec3( GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) , GetRand( MAX_VOLUME ) );

#ifdef USE_SHADER
		//4 ���������� ��� osg::PrimitiveSet::QUADS
		v->push_back( pos );
		v->push_back( pos );
		v->push_back( pos );
		v->push_back( pos );
#else
		//4 ���������� ��� osg::PrimitiveSet::QUADS
		v->push_back( pos + osg::Vec3( -MAX_SIZE , 0 , -MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( MAX_SIZE , 0 , -MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( MAX_SIZE , 0 , MAX_SIZE ) );
		v->push_back( pos + osg::Vec3( -MAX_SIZE , 0 , MAX_SIZE ) );
#endif

		//���� �������,����� �� ���� �������
		n->push_back( osg::Vec3( 0, -1 , 0 ) );
	
		//���������� ����������
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
	//�������� ��������� �����
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;
}

void Billboards::AddShader()
{
	//�������� ������ � �����
	osg::StateSet* ss = m_rootGroup->getOrCreateStateSet();

	//������� ��������� ���������
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/billboard.vert" );
	LoadShaderSource( FragObj , "glsl/billboard.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//���������� uniform'�� ��� ������ � ����������� ��������
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
