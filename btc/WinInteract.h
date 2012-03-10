#ifndef _WIN_INTERACT_H_
#define _WIN_INTERACT_H_

#include <Windows.h>

#include "StrGen.h"

class WinInteract
{
public:
	WinInteract();
	~WinInteract();

	//задержка iSec секунд
	void Delay(int iSec);

	//загрузить правила перебора
	void LoadRules(const char* pFile);

	//загрузить последний прерванный сеанс
	void LoadLastSave(const char* pFile);

	//определение нажатия на клавиши
	bool KeyPressDetect();

	//обработать шаг логики
	bool Process();
private:

	//послать сообщения нажатия на кнопки
	void SendKeyPress(HWND hWnd, const std::string& sTry);

	//сообщение о нажатии на enter посылаем отдельно
	void SendEnterPress(HWND hWnd);

	//удалить ранее введенный текст
	void ClearTextEdit(HWND hWnd);

	//произвести обработку ситуации с сообщением об ошибке
	void ProcessErrorWin(HWND hWnd);

	//генерилка строк
	StrGen m_StrGen;

	//длина предыдущей строки, которую нужно стереть 
	int m_iStrLen;
};

#endif	//_WIN_INTERACT_H_