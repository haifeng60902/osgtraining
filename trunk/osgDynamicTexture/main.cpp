#include "DynamicTexture.h"
#include <osgViewer/Viewer>

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	
	//создать класс с динамической текстурой
	DynamicTexture dynTexture;

	//назначить данные просмотрщику
	viewer.setSceneData( dynTexture.getRootNode().get() );

	return viewer.run();
}