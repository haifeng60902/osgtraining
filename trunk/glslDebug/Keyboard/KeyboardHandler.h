#ifndef _KEYBOARD_HANDLER_H_
#define _KEYBOARD_HANDLER_H_

#include <osgGA/GUIEventHandler>

class KeyboardHandler : public osgGA::GUIEventHandler 
{
public:
	KeyboardHandler();
	~KeyboardHandler();

	bool handle( const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa );

private:
	//положение мыши на относительно окна
	float m_fX;
	float m_fY;
};

#endif	//_KEYBOARD_HANDLER_H_