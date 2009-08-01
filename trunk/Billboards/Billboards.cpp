#include "Billboards.h"

#include "constant.h"

#include "FakeTree.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/FileUtils>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osg/AlphaFunc>

Billboards::Billboards()
{
	//�������� ������ ��� �������� ������
	m_rootGroup = new osg::Group;

	m_Group = new osg::Group;

	m_rootGroup->addChild( m_Group );

	//��������� ��������
	LoadTexture();

	srand( 1 );

	//������������ ����� � ��������
	buildSceneShader();

	//�������� ���������
	AddPlane();

	//�������� � ����� �������� �����
	m_rootGroup->addChild( m_LightSource.getRootNode().get() );

	osg::StateSet* ss = m_Group->getOrCreateStateSet();

	//��������� ���������
	SetupStateSet( ss );
}

Billboards::~Billboards()
{

}

void Billboards::LoadTexture()
{
	//��������� ��������

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( "pic/AmericanElmLeaves_RT_1.tga" );

	// Attach the image in a Texture2D object
	m_Tex0 = new osg::Texture2D;
	m_Tex0->setImage( image0.get() );

	//���������� �������, ���������� ������������ � RAM
	m_Tex0->setUnRefImageDataAfterApply( true );
}

void Billboards::buildSceneShader()
{
	//������������ ����� � ��������

	for ( int i = -2 ; i < 3 ; ++i )
		for ( int j = -2 ; j < 3 ; ++j )
		{
			osg::ref_ptr< FakeTree > tree = new FakeTree( osg::Vec3( i * 10 , j * 10 , 10 ) );

			m_Group->addChild( tree->getRootTransform().get()  );
		}
}

void Billboards::SetupStateSet( osg::StateSet* ss )
{
	//��������� ���������

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	ss->setTextureAttributeAndModes( 0, m_Tex0.get() , osg::StateAttribute::ON );

	//�������� ������ � �����
	AddShader( ss );

	//�������� ������ ��� ������� ������������
	ss->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

	// Turn on alpha testing
	osg::AlphaFunc* af = new osg::AlphaFunc(
		osg::AlphaFunc::GREATER, 0.34 );
	
	ss->setAttributeAndModes( af );
}

float Billboards::GetRand( float fScale )
{
	//�������� ��������� �����
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;
}

void Billboards::AddShader( osg::StateSet* ss )
{
	//�������� ������ � �����

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

	//������������ ��������� ��������� �����
	osg::Uniform *lightPos = new osg::Uniform( "lightPos" , osg::Vec3(0,0,0) );
	ss->addUniform( lightPos );

	//�������� Uniform
	m_LightSource.SetUniform( lightPos );
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
	//�������� ���������

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE );

	//4 ���������� ��� osg::PrimitiveSet::QUADS
	v->push_back( osg::Vec3( -MAX_VOLUME * 5 , -MAX_VOLUME * 5, 0 ) );
	v->push_back( osg::Vec3( MAX_VOLUME * 5, -MAX_VOLUME * 5, 0 ) );
	v->push_back( osg::Vec3( MAX_VOLUME * 5, MAX_VOLUME * 5, 0 ) );
	v->push_back( osg::Vec3( -MAX_VOLUME * 5, MAX_VOLUME * 5, 0 ) );

	//���� �������,����� �� ���� �������
	n->push_back( osg::Vec3( 0, 0 , 1 ) );

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

	geode->addDrawable( geom.get() );

	m_rootGroup->addChild( geode.get() );
}