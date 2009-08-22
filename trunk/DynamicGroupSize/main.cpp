#include "DynamicGroupSize.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

int main()
{
	osg::ref_ptr< DynamicGroupSize > dynSize = new DynamicGroupSize;

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	//	viewer.addEventHandler( new KeyboardHandler );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 45.0, 600.0/ 1024.0 , 1.0 , 35000.0 );

	viewer.setSceneData( dynSize->getRootNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// Display, and main loop.
	return viewer.run();	
}