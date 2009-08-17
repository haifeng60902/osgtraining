#include "SimpleScene.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <iostream>

int main()
{
	osg::ref_ptr< SimpleScene > simple = new SimpleScene;

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 45.0, 1050.0 / 1680.0 , 1.0 , 20000.0 );

	viewer.setSceneData( simple->getRootNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// Display, and main loop.
	return viewer.run();
}