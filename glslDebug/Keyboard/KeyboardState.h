#ifndef _KEYBOARD_STATE_H_
#define _KEYBOARD_STATE_H_

#include "Singleton.h"
#include "binEvents.h"

class KeyboardState : public Singleton< KeyboardState >
{
public:
	KeyboardState();
	~KeyboardState();

	//получить доступ к состоянию клавиатуры
	binEvents &GetEvents(){ return m_binEvents; };
private:
	//состояние клавиатуры
	binEvents m_binEvents;
};

#endif	//_KEYBOARD_STATE_H_