#include "KeyboardHandler.h"

#include "DynamicFrustum.h"

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
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			if ( ea.getKey()=='1' )
			{
				//создать фрустум
				DynamicFrustum::Instance().CreateFrustum();
			}

			return false;
		}

	default:
		return false;
	}

	return false;
}