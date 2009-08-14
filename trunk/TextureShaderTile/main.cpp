#include "TextureShaderTile.h"

#include "KeyboardHandler.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

int main()
{
	osg::ref_ptr< TextureShaderTile > plane = new TextureShaderTile;

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// add the stats handler
	viewer.addEventHandler( new osgViewer::StatsHandler );

	KeyboardHandler *key = new KeyboardHandler;

	//передать Uniform смещения
	key->SetOffsetX( plane->GetUniformOffsetX().get() );
	key->SetOffsetY( plane->GetUniformOffsetY().get() );

	key->SetScaleX( plane->GetUniformScaleX().get() );
	key->SetScaleY( plane->GetUniformScaleY().get() );

	key->SetOffsetScaleX( plane->GetUniformOffsetScaleX().get() );
	key->SetOffsetScaleY( plane->GetUniformOffsetScaleY().get() );

	viewer.addEventHandler( key );

	//настройка камеры
	viewer.getCamera()->setProjectionMatrixAsPerspective( 45.0, 1050.0 / 1680.0 , 1.0 , 30000.0 );

	viewer.setSceneData( plane->getRootNode().get() );

	viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR); 

	// Display, and main loop.
	return viewer.run();
}