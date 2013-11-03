#include <iostream>

#include "btc/WinInteract.h"

int main()
{
	//класс для работы с окнами
	WinInteract mInter;

	//ждать правильного фокуса
	mInter.Delay(5);

	//загрузить правила перебора pass_rule.txt
	mInter.LoadRules("keys.txt");

	//загрузить последний прерванный сеанс
	mInter.LoadLastSave("try.txt");
	
	bool bStop = false;
	while ( !bStop )
	{
		//определение нажатия на клавиши
		bStop = mInter.KeyPressDetect();

		//подсчет тиков в секунду
		bStop = bStop||mInter.Process();
	}
}