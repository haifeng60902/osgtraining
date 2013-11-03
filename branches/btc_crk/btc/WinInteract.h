#ifndef _WIN_INTERACT_H_
#define _WIN_INTERACT_H_

#include <Windows.h>

#include "StrGen.h"
#include "StrDecode.h"

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

	//загрузить последний прерванный сеанс
	void LoadEncode(const char* pFile);

	//определение нажатия на клавиши
	bool KeyPressDetect();

	//обработать шаг логики
	bool Process();

	//для отладки
	std::string GenNextStr();

	//сохранить текущий результат
	void SaveStr();
private:

	//послать сообщения нажатия на кнопки
	void SendKeyPress(HWND hWnd, const std::string& sTry);

	//сообщение о нажатии на enter посылаем отдельно
	void SendEnterPress(HWND hWnd);

	//удалить ранее введенный текст
	void ClearTextEdit(HWND hWnd);

	//произвести обработку ситуации с сообщением об ошибке
	void ProcessErrorWin();

	//генерилка строк
	StrGen m_StrGen;

	//перебор кодов символов
	StrDecode m_StrDecode;

	//длина предыдущей строки, которую нужно стереть 
	int m_iStrLen;
};

#endif	//_WIN_INTERACT_H_