#include "TerrainNode.h"

#include "FrustumSingleton.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Camera>
#include <osgGA/TrackballManipulator>

int main()
{
	osg::ref_ptr< TerrainNode > terrain = new TerrainNode;

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	//	viewer.addEventHandler( new KeyboardHandler );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 45 , 1050.0 / 1680.0 , 1.0 , 30000.0 );
	//viewer.getCamera()->setProjectionMatrixAsPerspective( 112.5 , 1024.0 / 1280.0 , 1.0 , 30000.0 );

	viewer.setSceneData( terrain->getRootNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	viewer.setCameraManipulator( new osgGA::TrackballManipulator );

	//viewer.setUpViewInWindow(40, 40, 640, 480 );

	// Override threading model
	viewer.setThreadingModel(osgViewer::Viewer::CullDrawThreadPerContext);

	// Display, and main loop.
	while (!viewer.done())
	{
		//обновить информацию матрицы проекции
		FrustumSingleton::Instance().UpdateProjection( 
			viewer.getCamera()->getProjectionMatrix() );

		osg::Matrix inv_view = osg::Matrix::inverse( viewer.getCamera()->getViewMatrix() );

		//обновить плоскости отсечения камеры
		FrustumSingleton::Instance().UpdateFrustum( inv_view );

		osg::Vec3 pos = osg::Vec3( inv_view( 3 , 0 ) , inv_view( 3 , 1 ) , inv_view( 3 , 2 ) );

		//задать положение наблюдателя
		FrustumSingleton::Instance().SetViewPos( pos );

		viewer.frame();
	}

	//return viewer.run();
	return 0;
}