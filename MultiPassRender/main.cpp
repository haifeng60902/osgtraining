#include "binDef.h"
#include "CameraUpdateCallback.h"
#include "osgPerspectiveTexturePlane.h"
#include "KeyboardHandler.h"
#include "binEvents.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

#include <iostream>

int main()
{
	binEvents ff;

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	//viewer.addEventHandler( new osgViewer::StatsHandler );

	osg::ref_ptr< KeyboardHandler > keyboard = new KeyboardHandler;

	// add the pick handler
	viewer.addEventHandler( keyboard.get() );

	//размер окна
	viewer.setUpViewInWindow(10, 10, WIN_W, WIN_H );
	//viewer.setUpViewOnSingleScreen( 0 );

	viewer.getCamera()->setClearColor(osg::Vec4( 0.1f , 0.2f , 0.3f , 1.0f ));

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsFrustum( -HALF_SIZE , HALF_SIZE 
		, -HALF_SIZE * WIN_H / WIN_W , HALF_SIZE * WIN_H / WIN_W , 1.0 , 2970.0 );

	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/mi17/MI_17_lod.flt" );
	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );

	osg::ref_ptr< osg::MatrixTransform > mTr = new osg::MatrixTransform;
	osg::Matrix mT;
	mT.makeTranslate( 0, 0, 0);
	mTr->setMatrix( mT );
	
	mTr->addChild( node.get() );

	osgPerspectiveTexturePlane perspPlane;

	osg::ref_ptr< osg::Group > group = new osg::Group;
	group->addChild( mTr.get() );
	group->addChild( perspPlane.GetNode().get() );

	viewer.setSceneData( group.get() );

	osg::StateSet* stateNode = viewer.getCamera()->getOrCreateStateSet();

	//выключаем освещение
	stateNode->setMode( GL_LIGHTING , osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	float fY = 0.0f;

	viewer.getCamera()->setUpdateCallback( new CameraUpdateCallback() );

	// Display, and main loop.
	while (!viewer.done())
	{
		viewer.frame();
	}
}