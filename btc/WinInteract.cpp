#include "WinInteract.h"

#include <iostream>
#include <conio.h>

WinInteract::WinInteract()
{
	m_iStrLen=0;
}

WinInteract::~WinInteract()
{

}

void WinInteract::Delay(int iSec)
{
	//задержка iSec секунд
	std::cout<<"wait:";
	for (int i=iSec;i>0;--i)
	{
		Sleep(1000);
		std::cout<<i<<" ";
	}
	std::cout<<"\n";
}

void WinInteract::LoadRules(const char* pFile)
{
	//загрузить правила перебора
	m_StrGen.LoadPassRule(pFile);
}

bool WinInteract::KeyPressDetect()
{
	//определение нажати€ на клавиши
	char cT('_');
	if ( kbhit() )
		cT = getch();

	if ( cT == 27 )
		return true;

	return false;
}

bool WinInteract::Process()
{
	//обработать шаг логики
	
	HWND hWnd=FindWindow("QWidget","–азблокировать бумажник");
	if (hWnd)
	{
		//удалить ранее введенный текст
		ClearTextEdit(hWnd);

		//следующа€ последовательность
		std::string sTry=m_StrGen.GenNextStr();

		//послать сообщени€ нажати€ на кнопки
		SendKeyPress(hWnd, sTry);

		//сообщение о нажатии на enter посылаем отдельно
		SendEnterPress(hWnd);

		//произвести обработку ситуации с сообщением об ошибке
		ProcessErrorWin(hWnd);

		//запомнить длину строки
		m_iStrLen=sTry.size();

		Sleep(10);

		return false;
	}

	return true;
}

void WinInteract::SendKeyPress(HWND hWnd, const std::string& sTry)
{
	//послать сообщени€ нажати€ на кнопки
	for (int i=0;i<sTry.size();++i)
	{
		SendMessage( hWnd, WM_KEYDOWN, sTry[i], 0 );
		SendMessage( hWnd, WM_KEYUP, sTry[i], 0 );
	}
}

void WinInteract::SendEnterPress(HWND hWnd)
{
	//сообщение о нажатии на enter посылаем отдельно
	SendMessageTimeout(hWnd, WM_KEYDOWN, 13, 0 ,SMTO_BLOCK, 10,NULL);
	SendMessageTimeout(hWnd, WM_KEYUP, 13, 0 ,SMTO_BLOCK, 10,NULL);
}

void WinInteract::ClearTextEdit(HWND hWnd)
{
	//удалить ранее введенный текст
	SendMessage( hWnd, WM_KEYDOWN, VK_HOME, 0 );
	SendMessage( hWnd, WM_KEYUP, VK_HOME, 0 );
	for (int i=0;i<m_iStrLen;++i)
	{
		SendMessage( hWnd, WM_KEYDOWN, VK_DELETE, 0 );
		SendMessage( hWnd, WM_KEYUP, VK_DELETE, 0 );
	}
}

void WinInteract::ProcessErrorWin(HWND hWnd)
{
	//произвести обработку ситуации с сообщением об ошибке
	for (int i=0;i<100;++i)
	{
		HWND hWndErr=FindWindow("QWidget","–азблокировка бумажника не удалась");
		if (hWndErr)
			SendEnterPress(hWndErr);
		else
			return;
	}
	std::cout<<"\nerror\n";
}