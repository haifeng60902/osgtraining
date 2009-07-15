#include "Lighting.h"

#include <osgViewer/Viewer>

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	osg::ref_ptr< Lighting > lighting= new Lighting;

	//назначить данные просмотрщику
	viewer.setSceneData( lighting->getRootNode().get() );

	return viewer.run();
}