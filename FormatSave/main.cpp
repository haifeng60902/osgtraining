#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <iostream>

int main()
{
	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	//	viewer.addEventHandler( new KeyboardHandler );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 45.0, 600.0/ 1024.0 , 1.0 , 35000.0 );

	//добавить модель земной поверхности
	osg::ref_ptr<osg::Node> root = osgDB::readNodeFile( "ball.osg" );

	bool res = osgDB::writeNodeFile( *root , "test.stl" ); 

	viewer.setSceneData( root.get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// Display, and main loop.
	return viewer.run();
}