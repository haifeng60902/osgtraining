#include "binDef.h"
#include "CameraUpdateCallback.h"
#include "UfoManipulator.h"
#include "osgTexturePlane.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>

#include <iostream>

int main()
{
	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	//viewer.addEventHandler( new osgViewer::StatsHandler );

	//������ ����
	viewer.setUpViewInWindow(10, 10, WIN_W, WIN_H );

	//��������� ������
	viewer.getCamera()->setProjectionMatrixAsOrtho( 0.0 , WIN_W , 0.0 , WIN_H , 1.0 , 200.0 );

	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );
	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/mi17/MI_17_lod.flt" );

	//������� ��������� � ���������
	osgTexturePlane plane;
	viewer.setSceneData( plane.GetNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	float fY = 0.0f;

	//viewer.getCamera()->setUpdateCallback( new CameraUpdateCallback() );

	// set up the camera manipulation with out custom manipultor
	//viewer.setCameraManipulator( new UfoManipulator() );

	// Display, and main loop.
	while (!viewer.done())
	{
		osg::Matrix mtTr;
		mtTr.makeTranslate( 0, 0 , -100 );
		
		//������ ���� ��������
		viewer.getCamera()->setViewMatrix( mtTr );

		viewer.frame();
	}

	//viewer.run();
}