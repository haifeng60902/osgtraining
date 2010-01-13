#include "binDef.h"
#include "CameraUpdateCallback.h"
#include "UfoManipulator.h"
#include "osgTexturePlane.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>

#include <iostream>

//#define ORTHO2D

int main()
{
	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	//viewer.addEventHandler( new osgViewer::StatsHandler );

	//размер окна
	viewer.setUpViewInWindow(10, 10, WIN_W, WIN_H );

#ifdef ORTHO2D
	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsOrtho( 0.0 , WIN_W , 0.0 , WIN_H , 1.0 , 200.0 );

	//простая геометрия с текстурой
	osgTexturePlane plane;
	viewer.setSceneData( plane.GetNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// Display, and main loop.
	while (!viewer.done())
	{
		osg::Matrix mtTr;
		mtTr.makeTranslate( 0, 0 , -100 );

		//задать явно смещение
		viewer.getCamera()->setViewMatrix( mtTr );

		viewer.frame();
	}
#else
	viewer.getCamera()->setClearColor(osg::Vec4( 0.1f , 0.2f , 0.3f , 1.0f ));

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 45.0, WIN_W / WIN_H , 1.0 , 35000.0 );

	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );
	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/mi17/MI_17_lod.flt" );

	viewer.setSceneData( node.get() );

	osg::StateSet* stateNode = viewer.getCamera()->getOrCreateStateSet();

	//выключаем освещение
	stateNode->setMode( GL_LIGHTING , osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	float fY = 0.0f;

	viewer.getCamera()->setUpdateCallback( new CameraUpdateCallback() );

	// set up the camera manipulation with out custom manipultor
	//viewer.setCameraManipulator( new UfoManipulator() );

	// Display, and main loop.
	while (!viewer.done())
	{
		osg::Matrix mtTr;
		mtTr.makeTranslate( 0, 0 , -100 );

		//задать явно смещение
		viewer.getCamera()->setViewMatrix( mtTr );

		viewer.frame();
	}
#endif

	//viewer.run();
}