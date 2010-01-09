#include "osgTestPattern.h"

#include "binDef.h"

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
	viewer.setUpViewInWindow(10, 10, WIN_W, WIN_H );
	viewer.getCamera()->setProjectionMatrixAsOrtho( 0.0 , WIN_W , 0.0 , WIN_H , 1.0 , 200.0 );

	// set viewport
	//viewer.getCamera()->setViewport(0,0,640,480); 

	osgTestPattern node;
	viewer.setSceneData( node.GetNode().get() );

	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );
	//viewer.setSceneData( node.get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	float fY = 0.0f;

	// Display, and main loop.
	while (!viewer.done())
	{
		osg::Matrix mtTr;
		mtTr.makeTranslate( 0, 0 , -100 );
		//viewer.getCamera()->setProjectionMatrixAsOrtho2D( -4.0 , 4.0 , -3.0 , 3.0 );

		//viewer.getCamera()->setProjectionMatrixAsOrtho( -fY * 4.0 , fY * 4.0 , -fY * 3.0 , fY * 3.0 , 1, 1000 );

		//задать явно смещение
		viewer.getCamera()->setViewMatrix( mtTr );
		
		viewer.frame();

		fY += 0.1;

		std::cout << fY << " ";
	}

	//viewer.run();
}