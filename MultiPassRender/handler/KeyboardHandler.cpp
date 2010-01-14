#include "KeyboardHandler.h"

#include <osgViewer/Viewer>

#include <iostream>

KeyboardHandler::KeyboardHandler()
{

}

KeyboardHandler::~KeyboardHandler()
{

}

bool KeyboardHandler::handle( const osgGA::GUIEventAdapter& ea,
							 osgGA::GUIActionAdapter& aa )
{
	osgViewer::Viewer* viewer =
		dynamic_cast<osgViewer::Viewer*>( &aa );
	if (!viewer)
		return( false );

	switch(ea.getEventType())
	{
	case( osgGA::GUIEventAdapter::KEYDOWN ):
		{
			if ( ea.getKey()=='o' )
			{
			
			}
			return false;
		}
	case osgGA::GUIEventAdapter::MOVE:
		{
			// Record mouse location for the button press
			//   and move events.
			m_fX = ea.getX();
			m_fX = ea.getY();

			std::cout << ea.getX() << " " << ea.getY() << " "
				<< ea.getXnormalized() << " " << ea.getYnormalized() << "\n";
			return( false );
		}

	default:
		return false;
	}

	return false;
}