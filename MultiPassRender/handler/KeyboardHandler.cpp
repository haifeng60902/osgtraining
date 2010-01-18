#include "KeyboardHandler.h"

#include "KeyboardState.h"

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

	//получить доступ к состоянию клавиатуры
	binEvents &mEvents = KeyboardState::Instance().GetEvents();

	switch(ea.getEventType())
	{
	case( osgGA::GUIEventAdapter::KEYDOWN ):
		{
			//клавиша нажата
			unsigned char mKey = ea.getKey();
			mEvents.m_bKey[ mKey ] = true;

			return false;
		}
	case( osgGA::GUIEventAdapter::KEYUP ):
		{
			//клавиша нажата
			unsigned char mKey = ea.getKey();
			mEvents.m_bKey[ mKey ] = false;

			return false;
		}
	case osgGA::GUIEventAdapter::MOVE:
		{
			// Record mouse location for the button press
			//   and move events.
			mEvents.m_dX = ea.getXnormalized();
			mEvents.m_dY = ea.getYnormalized();

			return false;
		}

	default:
		return false;
	}

	return false;
}