#include "PerspectiveTexturePlane.h"

#include "binDef.h"
#include "UpdClbkPerspectiveTexturePlane.h"

#include <osg/Geometry>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/Program>


PerspectiveTexturePlane::PerspectiveTexturePlane()
{
	//������� ���������
	CreateGeom();

	//�������� ������
	AddCamera();

	//�������� ������
	AddShader();

	//������ �������� ����� ���������� ��� ���� ���������
	m_Transform->setUpdateCallback( new UpdClbkPerspectiveTexturePlane() );
}

PerspectiveTexturePlane::~PerspectiveTexturePlane()
{

}

void PerspectiveTexturePlane::CreateGeom()
{
	//������� ���������
	osg::ref_ptr< osg::Geode > mGeode = new osg::Geode;

	//��������� ��� ��������������
	osg::ref_ptr< osg::Geometry > mGeom = new osg::Geometry;

	//������� ������
	m_Transform = new osg::MatrixTransform;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	mGeom->setVertexArray( v.get() );

	v->push_back( osg::Vec3( -HALF_SIZE , 1.0 , -HALF_SIZE * WIN_H / WIN_W ) );
	v->push_back( osg::Vec3( HALF_SIZE , 1.0 , -HALF_SIZE * WIN_H / WIN_W ) );
	v->push_back( osg::Vec3( HALF_SIZE , 1.0 , HALF_SIZE * WIN_H / WIN_W ) );
	v->push_back( osg::Vec3( -HALF_SIZE , 1.0 , HALF_SIZE * WIN_H / WIN_W ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	mGeom->setNormalArray( n.get() );
	mGeom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > c = new osg::Vec3Array;
	mGeom->setColorArray( c.get() );
	mGeom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec3( 1.f, 1.f, 1.f ) );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	mGeom->setTexCoordArray( 0, tc.get() );
	
	tc->push_back( osg::Vec2( 0 , 0 ) );
	tc->push_back( osg::Vec2( 1.0 , 0 ) );
	tc->push_back( osg::Vec2( 1.0 , 1.0 ) );
	tc->push_back( osg::Vec2( 0 , 1.0 ) );

	mGeom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS , 0, v->size() ) );

	mGeode->addDrawable( mGeom.get() );

	m_Transform->addChild( mGeode.get() );
}

void PerspectiveTexturePlane::AddCamera()
{

	//�������� ������
	m_Camera0.Init();

	//�������� ������ � ��������� ����
	osg::StateSet* state = m_Transform->getOrCreateStateSet();

	//���������� ��������
	state->setTextureAttributeAndModes( 0 , m_Camera0.GetTexture().get() , osg::StateAttribute::ON );

	//��������� ���������
	state->setMode( GL_LIGHTING , osg::StateAttribute::OFF );

	//�������� ���� ������
	m_Transform->addChild( m_Camera0.GetCameraNode().get() );
}

void PerspectiveTexturePlane::AddShader()
{
	//�������� ������
	osg::StateSet* stateNode = m_Transform->getOrCreateStateSet();

	//������� ��������� ���������
	osg::Program* program = new osg::Program;
	program->setName( "plane_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/plane.vert" );
	LoadShaderSource( FragObj , "glsl/plane.frag" );

	stateNode->setAttributeAndModes( program, osg::StateAttribute::ON );

	//���������� uniform'�� ��� ������ � ����������� ��������
	stateNode->addUniform( new osg::Uniform( "u_texture0" , 0 ) );

}

void PerspectiveTexturePlane::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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