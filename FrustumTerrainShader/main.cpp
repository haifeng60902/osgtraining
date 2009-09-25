//#include "TerrainNode.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

int main()
{
//	osg::ref_ptr< TerrainNode > terrain = new TerrainNode;

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	//	viewer.addEventHandler( new KeyboardHandler );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 112.5, 1050.0 / 1680.0 , 1.0 , 30000.0 );

//	viewer.setSceneData( terrain->getRootNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	//viewer.setUpViewInWindow(40, 40, 640, 480 );

	// Display, and main loop.
	return viewer.run();
}