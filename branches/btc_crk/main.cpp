#include <iostream>

#include "btc/WinInteract.h"

int main()
{
	//����� ��� ������ � ������
	WinInteract mInter;

	//����� ����������� ������
	mInter.Delay(5);

	//��������� ������� ��������
	mInter.LoadRules("pass_rule.txt");
	
	bool bStop = false;
	while ( !bStop )
	{
		//����������� ������� �� �������
		bStop = mInter.KeyPressDetect();

		//������� ����� � �������
		bStop = bStop||mInter.Process();
	}
}