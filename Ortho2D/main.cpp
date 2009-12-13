#include "osgTestPattern.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>

#include <iostream>

int main()
{
	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	//настройка камеры
	//viewer.getCamera()->setProjectionMatrixAsPerspective( 45.0, 600.0/ 1024.0 , 1.0 , 35000.0 );
	viewer.getCamera()->setProjectionMatrixAsOrtho( -6 , 6 , -4 , 4 , -1 , 10000 );

	viewer.setUpViewInWindow(40, 40, 640, 480 );

	// set viewport
	//viewer.getCamera()->setViewport(0,0,640,480); 

	//osgTestPattern node;
	//viewer.setSceneData( node.GetNode().get() );
	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "extern/gen_airport.ive" );
	viewer.setSceneData( node.get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	osg::Matrix mtTr;
	float fY = 0.0f;

	// Display, and main loop.
	while (!viewer.done())
	{
		mtTr.makeTranslate( 0, -fY , 0 );

		//задать явно смещение
		viewer.getCamera()->setViewMatrix( mtTr );
		
		viewer.frame();

		fY -= 0.01;

		std::cout << fY << " ";
	}

	//viewer.run();
}