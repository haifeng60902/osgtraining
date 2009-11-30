#include "ticpp.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
 
int main()
{


//	try
	{
		// Load a document
		ticpp::Document doc( "tree.xml" );
		doc.LoadFile();

		// Get an element by chaining calls - no return values to check, no TiXmlHandle
		ticpp::Element* pElem = dynamic_cast< ticpp::Element* >( doc.FirstChildElement() );

		ticpp::Iterator< ticpp::Element > child( "branch" );
		for ( child = child.begin( doc.FirstChildElement() ); child != child.end(); child++ )
		{
			std::string sFile;
			child->GetAttribute( "texture" , &sFile );
			int a = 1;
		}

//////////////////////////////////////////////////////////////////////////
		ticpp::Iterator< ticpp::Element > childF( "fronds" );
		for ( childF = childF.begin( doc.FirstChildElement() ); childF != childF.end(); childF++ )
		{
			std::string sFile;
			childF->GetAttribute( "texture" , &sFile );
			int a = 1;
		}

		// do something useful here
	}
//	catch( ticpp::Exception& ex )
	{
		// If any function has an error, execution will enter here.
		// Report the error
//		std::cout << ex.what();
	}

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