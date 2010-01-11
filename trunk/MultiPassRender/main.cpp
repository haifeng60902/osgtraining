#include "binDef.h"
#include "CameraUpdateCallback.h"
#include "UfoManipulator.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>

#include <iostream>

int main()
{
	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	//viewer.addEventHandler( new osgViewer::StatsHandler );

	//размер окна
	viewer.setUpViewInWindow(10, 10, WIN_W, WIN_H );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 45.0, WIN_W / WIN_H , 1.0 , 35000.0 );

	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );
	viewer.setSceneData( node.get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	float fY = 0.0f;

	//viewer.getCamera()->setUpdateCallback( new CameraUpdateCallback() );

	// set up the camera manipulation with out custom manipultor
	viewer.setCameraManipulator( new UfoManipulator() );

	// Display, and main loop.
	while (!viewer.done())
	{
		osg::Matrix mtTr;
		mtTr.makeRotate( osg::DegreesToRadians( -90.0 ) , 1, 0 , 0 );
		
		//задать явно смещение
		//viewer.getCamera()->setViewMatrix( mtTr );

		viewer.frame();

		fY += 0.01;

		//std::cout << fY << " ";
	}

	//viewer.run();
}