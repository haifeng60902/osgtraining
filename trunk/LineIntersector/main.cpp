#include "DynamicLines.h"

#include <osgViewer/Viewer>
#include <osg/ref_ptr>

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	osg::ref_ptr< DynamicLines > _lines = new DynamicLines;

	//��������� ������ ������������
	viewer.setSceneData( _lines->getRootNode().get() );

	return viewer.run();
}