#include <iostream>

#include "binDef.h"
#include "KeyboardHandler.h"
#include "MainNode.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

int main()
{
	// Create a Viewer.
	osgViewer::Viewer viewer;

	osg::ref_ptr< KeyboardHandler > keyboard = new KeyboardHandler;

	// add the pick handler
	viewer.addEventHandler( keyboard.get() );

	//размер окна
	viewer.setUpViewInWindow(10, 10, WIN_W, WIN_H );
	//viewer.setUpViewOnSingleScreen( 0 );

	viewer.getCamera()->setClearColor(osg::Vec4( 0.1f , 0.2f , 0.3f , 1.0f ));

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsFrustum( -HALF_SIZE , HALF_SIZE 
		, -HALF_SIZE * WIN_H / WIN_W , HALF_SIZE * WIN_H / WIN_W , 1.0 , 30.0 );

	//главный узел, в которой входит остальная сцена
	MainNode m_MainNode;

	m_MainNode.Init();

	//добавить в сцену корневой узел
	viewer.setSceneData( m_MainNode.GetNode().get() );

	std::cout << "ok\n";
}