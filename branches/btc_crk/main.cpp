#include <iostream>

#include "btc/WinInteract.h"

int main()
{
	//класс для работы с окнами
	WinInteract mInter;

	//ждать правильного фокуса
	mInter.Delay(5);

	//загрузить правила перебора
	mInter.LoadRules("pass_rule.txt");
	
	bool bStop = false;
	while ( !bStop )
	{
		//определение нажатия на клавиши
		bStop = mInter.KeyPressDetect();

		//подсчет тиков в секунду
		bStop = bStop||mInter.Process();
	}
}