#include "xmlRoot/xmlRoot.h"

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

int main()
{
	xmlRoot::Instance().Init( "tree.xml" );

	// Create a Viewer.
	osgViewer::Viewer viewer;

	// Display, and main loop.
	return viewer.run();
}