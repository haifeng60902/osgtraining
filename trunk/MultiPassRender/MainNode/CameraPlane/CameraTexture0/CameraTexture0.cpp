#include "CameraTexture0.h"

#include "binDef.h"
#include "UpdateCallbackCamera0.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Program>

CameraTexture0::CameraTexture0()
{

}

CameraTexture0::~CameraTexture0()
{

}

void CameraTexture0::Init()
{
	//������������� ����-������

	//������ ����, �������� �������� � ������� ����� ����������� �����������
	//CreateTexture();

	//������� ��������
	CreateTextures();

	//�������� ������
	CreateCamera();

	//��������� ���� ������
	SetupCameraNode();

	//�������� ������
	AddShader();
}

void CameraTexture0::CreateTexture()
{
	//������ ����, �������� �������� � ������� ����� ����������� �����������
	m_Texture0 = new osg::Texture2D;
	m_Texture0->setTextureSize( WIN_W , WIN_H );
	//m_Texture->setInternalFormat(GL_RGBA);
	m_Texture0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
	m_Texture0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST);
	m_Texture0->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_EDGE); 
	m_Texture0->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_EDGE);

	m_Texture0->setResizeNonPowerOfTwoHint( false );

	m_Texture0->setInternalFormat( GL_RGBA32F_ARB );
	m_Texture0->setSourceFormat( GL_RGBA );
	m_Texture0->setSourceType( GL_FLOAT );
}

void CameraTexture0::CreateCamera()
{
	//�������� ������
	m_Camera = new osg::Camera;

	// set up the background color and clear mask.
	m_Camera->setClearColor(osg::Vec4( 0.2f , 0.2f , 0.2f , 0.5f ) );
	m_Camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//��������� ������
	m_Camera->setProjectionMatrixAsFrustum( -HALF_SIZE , HALF_SIZE 
		, -HALF_SIZE * WIN_H / WIN_W , HALF_SIZE * WIN_H / WIN_W , ZNEAR , ZFAR );	//max 29700

	osg::Matrix fr = m_Camera->getProjectionMatrix();

	//1 1.5 2

	// set view
	m_Camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	// set viewport
	m_Camera->setViewport( 0 , 0 , WIN_W , WIN_H );

	// set the camera to render before the main camera.
	m_Camera->setRenderOrder( osg::Camera::PRE_RENDER );

	// tell the camera to use OpenGL frame buffer object where supported.
	m_Camera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );

	//��������� �������� ������
	AttachTextures2Camera();
}

void CameraTexture0::SetupCameraNode()
{
	//��������� ���� ������
	osg::ref_ptr< osg::Node > node0 = osgDB::readNodeFile( "flt/sphere/sphere.flt" );

	//������������� ����������
	m_TestFarPlanes.Init();

	//������������� ��������������� ������������� ��������� �����
	m_LightPoint.Init();

	//��������� ������
	m_AnimatingModel.Init( "flt/mi17/MI_17_lod.flt" );

	//������ �������� ����� ���������� ��� ������ ��� ����� ���������� ����������� ������ ��������� � ������� �������
	m_Camera->setUpdateCallback( new UpdateCallbackCamera0() );

	m_Camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// add subgraph to render
	m_Camera->addChild( node0.get() );
	m_Camera->addChild( m_TestFarPlanes.GetPlane().get() );
	m_Camera->addChild( m_LightPoint.GetPoint().get() );
	m_Camera->addChild( m_AnimatingModel.GetNode().get() );
}

void CameraTexture0::AddShader()
{
//�������� ������
	osg::StateSet* stateNode = m_Camera->getOrCreateStateSet();

	//������� ��������� ���������
	osg::Program* program = new osg::Program;
	program->setName( "camera_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/camera0.vert" );
	LoadShaderSource( FragObj , "glsl/camera0.frag" );

	stateNode->setAttributeAndModes( program, osg::StateAttribute::ON );

	stateNode->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	stateNode->addUniform( new osg::Uniform( "fZNear" , ZNEAR ) );
	stateNode->addUniform( new osg::Uniform( "fZFar" , ZFAR ) );
}

void CameraTexture0::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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

void CameraTexture0::CreateTextures()
{
//������� ��������
	for ( int i = 0 ; i < 2 ; ++i )
	{
		m_ListTexture2D.push_back( new osg::Texture2D );
		m_ListTexture2D.back()->setTextureSize( WIN_W , WIN_H );
		
		m_ListTexture2D.back()->setFilter( osg::Texture::MIN_FILTER , osg::Texture::NEAREST );
		m_ListTexture2D.back()->setFilter( osg::Texture::MAG_FILTER , osg::Texture::NEAREST );
		m_ListTexture2D.back()->setWrap( osg::Texture::WRAP_S , osg::Texture::CLAMP_TO_EDGE ); 
		m_ListTexture2D.back()->setWrap( osg::Texture::WRAP_T , osg::Texture::CLAMP_TO_EDGE );

		m_ListTexture2D.back()->setResizeNonPowerOfTwoHint( false );

		//������ �������� ����� float32rgba
		//��������� 8��� RGBA
		switch ( i )
		{
		case  0:
			m_ListTexture2D.back()->setInternalFormat( GL_RGBA32F_ARB );	//GL_RGBA_FLOAT32_ATI	GL_RGBA32F_ARB
			m_ListTexture2D.back()->setSourceFormat( GL_RGBA );
			m_ListTexture2D.back()->setSourceType( GL_FLOAT );
			break;
		default:
			m_ListTexture2D.back()->setInternalFormat( GL_RGBA );
			break;
		}
	}
}

void CameraTexture0::AttachTextures2Camera()
{
	//��������� �������� ������
	int i = osg::Camera::COLOR_BUFFER0;
	for ( tListTexture2D::iterator it = m_ListTexture2D.begin() ; it != m_ListTexture2D.end() ; ++ it , ++i )
	{
		osg::Camera::BufferComponent bufComp = static_cast< osg::Camera::BufferComponent >( i );

		// attach the texture and use it as the color buffer.
		m_Camera->attach( bufComp , ( *it ).get() , 
			0, 0, false,
			0, 0 );
	}
}