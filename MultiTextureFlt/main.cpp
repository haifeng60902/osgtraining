#include <osgViewer/Viewer>

#include "Flt2Scene.h"

#include <iostream>

int main()
{

	// construct the viewer.
	osgViewer::Viewer viewer;

	osg::ref_ptr< Flt2Scene > _flt = new Flt2Scene;

	viewer.setSceneData( _flt->getRootNode().get() );

	return viewer.run();
}