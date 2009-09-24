#include "SimpleScene.h"

#include "KeyboardHandler.h"
#include "CullCallback.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <iostream>

int main()
{
	// Create a Viewer.
	osgViewer::Viewer viewer;

	osg::ref_ptr< SimpleScene > simple = new SimpleScene( viewer.getCamera() );

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	viewer.addEventHandler( new KeyboardHandler );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 30.0, 600.0 / 1024.0 , 1.0 , 200.0 );

	viewer.setSceneData( simple->getRootNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// Display, and main loop.
	return viewer.run();
}