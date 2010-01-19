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

	// Record mouse location for the button press
	//   and move events.
	mEvents.m_dX = ea.getXnormalized();
	mEvents.m_dY = ea.getYnormalized();


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
	case osgGA::GUIEventAdapter::PUSH:
	case osgGA::GUIEventAdapter::MOVE:
		{
			int mMask =  ea.getButtonMask();

			if ( mMask == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
				mEvents.m_bLeft = true;
			else
				if ( mMask == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
					mEvents.m_bRight = true;
			
			return false;
		}

	case osgGA::GUIEventAdapter::RELEASE:
		{
			int mMask =  ea.getButtonMask();

			if ( mMask == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
				mEvents.m_bLeft = false;
			else
				if ( mMask == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
					mEvents.m_bRight = false;

			return false;
		}

	default:
		return false;
	}

	return false;
}