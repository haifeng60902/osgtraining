#include <osgViewer/Viewer>

#include "GL2Scene.h"

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	// create the scene
	GL2ScenePtr gl2Scene = new GL2Scene;

	viewer.setSceneData( gl2Scene->getRootNode().get() );

	return viewer.run();
}