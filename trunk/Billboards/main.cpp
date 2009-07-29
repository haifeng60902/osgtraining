#include "Billboards.h"

#include <osgViewer/Viewer>
#include <osg/ref_ptr>

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	//набор billboard'ов
	osg::ref_ptr< Billboards > bill = new Billboards;

	//назначить данные просмотрщику
	viewer.setSceneData( bill->getRootGroup().get() );

	return viewer.run();
}