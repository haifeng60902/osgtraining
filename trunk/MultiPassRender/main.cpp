#include "binDef.h"
#include "CameraUpdateCallback.h"
#include "KeyboardHandler.h"
#include "binEvents.h"
#include "MainNode.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <iostream>

int main()
{
//////////////////////////////////////////////////////////////////////////
//тест rgba
	float c = 0.5;

	float p0 = c;
	float p1 = c * 255.0 - floor( c * 255.0 );
	float p2 = c * 255.0 * 255.0 - floor( c * 255.0 * 255.0 );
	float p3 = c * 255.0 * 255.0 * 255.0 - floor( c * 255.0 * 255.0 * 255.0 );

	unsigned char c0 = p0 * 255;
	unsigned char c1 = p1 * 255;
	unsigned char c2 = p2 * 255;
	unsigned char c3 = p3 * 255;

	int a = 1;
//////////////////////////////////////////////////////////////////////////
	binEvents ff;

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	//viewer.addEventHandler( new osgViewer::StatsHandler );

	osg::ref_ptr< KeyboardHandler > keyboard = new KeyboardHandler;

	// add the pick handler
	viewer.addEventHandler( keyboard.get() );

	//размер окна
	//viewer.setUpViewInWindow(10, 10, WIN_W, WIN_H );
	viewer.setUpViewOnSingleScreen( 0 );

	viewer.getCamera()->setClearColor(osg::Vec4( 0.1f , 0.2f , 0.3f , 1.0f ));

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsFrustum( -HALF_SIZE , HALF_SIZE 
		, -HALF_SIZE * WIN_H / WIN_W , HALF_SIZE * WIN_H / WIN_W , 1.0 , 2970.0 );

//////////////////////////////////////////////////////////////////////////
	//главный узел, в которой входит остальная сцена
	MainNode m_MainNode;

	m_MainNode.Init();

	//добавить в сцену корневой узел
	viewer.setSceneData( m_MainNode.GetNode().get() );
//////////////////////////////////////////////////////////////////////////

	osg::StateSet* stateNode = viewer.getCamera()->getOrCreateStateSet();

	//выключаем освещение
	stateNode->setMode( GL_LIGHTING , osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	float fY = 0.0f;

	viewer.getCamera()->setUpdateCallback( new CameraUpdateCallback() );

	// Display, and main loop.
	while (!viewer.done())
	{
		viewer.frame();
	}
}