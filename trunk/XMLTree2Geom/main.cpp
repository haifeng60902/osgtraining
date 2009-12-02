#include "xmlTree.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include "ticpp.h"

int main()
{
	xmlTree::Instance().Init( "tree.xml" );
	//////////////////////////////////////////////////////////////////////////
	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	//viewer.setSceneData( tree->getRootNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// Display, and main loop.
	return viewer.run();
}