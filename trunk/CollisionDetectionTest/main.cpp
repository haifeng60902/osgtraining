#include "CollisionDetectionScene.h"

#include "osgIsectorHAT.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osg/ref_ptr>

#include <iostream>

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	osg::ref_ptr< CollisionDetectionScene > _scene = new CollisionDetectionScene;

	//назначить данные просмотрщику
	viewer.setSceneData( _scene->getRootNode().get() );

	viewer.setCameraManipulator( new osgGA::TrackballManipulator );

	// Display, and main loop.
	while (!viewer.done())
	{
		CollisionDetectionScene::tListIsecHAT &listHAT = _scene->GetListIsecHAT();

		CollisionDetectionScene::tListIsecHAT::iterator it = listHAT.begin();
		CollisionDetectionScene::tListIsecHAT::iterator itE = listHAT.end();
		int i = 0;
		while( it != itE )
		{
			osgIsectorHAT *isecHAT =  dynamic_cast< osgIsectorHAT* >( it->get() );

			if ( isecHAT )
			{
				float res = isecHAT->GetHAT();

				if ( i == 0 )
					std::cout << res << " ";
			}

			++it;
			++i;
		}

		viewer.frame();
	}
}