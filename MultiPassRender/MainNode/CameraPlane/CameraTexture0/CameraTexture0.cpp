#include "CameraTexture0.h"

#include "binDef.h"
#include "UpdateCallbackCamera0.h"

#include <osgDB/ReadFile>

CameraTexture0::CameraTexture0()
{

}

CameraTexture0::~CameraTexture0()
{

}

void CameraTexture0::Init()
{
	//инициализация узла-камеры

	//первый этап, создание текстуры в которую будет происходить отображение
	CreateTexture();

	//создание камеры
	CreateCamera();

	//настройка узла камеры
	SetupCameraNode();
}

void CameraTexture0::CreateTexture()
{
	//первый этап, создание текстуры в которую будет происходить отображение
	m_Texture = new osg::Texture2D;
	m_Texture->setTextureSize( WIN_W , WIN_H );
	m_Texture->setInternalFormat(GL_RGBA);
	m_Texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
	m_Texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST);
	m_Texture->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_EDGE); 
	m_Texture->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_EDGE);

	m_Texture->setResizeNonPowerOfTwoHint( false );
}

void CameraTexture0::CreateCamera()
{
	//создание камеры
	m_Camera = new osg::Camera;

	// set up the background color and clear mask.
	m_Camera->setClearColor(osg::Vec4( 0.2f , 0.2f , 0.2f , 0.5f ) );
	m_Camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//настройка камеры
	m_Camera->setProjectionMatrixAsFrustum( -HALF_SIZE , HALF_SIZE 
		, -HALF_SIZE * WIN_H / WIN_W , HALF_SIZE * WIN_H / WIN_W , 1.0 , 2970.0 );

	// set view
	m_Camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	// set viewport
	m_Camera->setViewport( 0 , 0 , WIN_W , WIN_H );

	// set the camera to render before the main camera.
	m_Camera->setRenderOrder( osg::Camera::PRE_RENDER );

	// tell the camera to use OpenGL frame buffer object where supported.
	m_Camera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );

	// attach the texture and use it as the color buffer.
	m_Camera->attach(osg::Camera::COLOR_BUFFER, m_Texture.get() , 
		0, 0, false,
		0, 0 );
}

void CameraTexture0::SetupCameraNode()
{
	//настройка узла камеры
	osg::ref_ptr< osg::Node > node0 = osgDB::readNodeFile( "flt/sphere/sphere.flt" );
	osg::ref_ptr< osg::Node > node1 = osgDB::readNodeFile( "flt/mi17/MI_17_lod.flt" );

	//задать обратный вызов обновления для камеры так чтобы координаты виртуальной камеры совподали с главной камерой
	m_Camera->setUpdateCallback( new UpdateCallbackCamera0() );

	m_Camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	osg::StateSet* stateNode = m_Camera->getOrCreateStateSet();

	//выключаем освещение
	stateNode->setMode( GL_LIGHTING , osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );

	// add subgraph to render
	m_Camera->addChild( node0.get() );
	m_Camera->addChild( node1.get() );
}