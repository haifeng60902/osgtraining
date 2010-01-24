#ifndef _KEYBOARD_STATE_H_
#define _KEYBOARD_STATE_H_

#include "Singleton.h"
#include "binEvents.h"

class KeyboardState : public Singleton< KeyboardState >
{
public:
	KeyboardState();
	~KeyboardState();

	//�������� ������ � ��������� ����������
	binEvents &GetEvents(){ return m_binEvents; };
private:
	//��������� ����������
	binEvents m_binEvents;
};

#endif	//_KEYBOARD_STATE_H_