#include <iostream>

#include "btc/WinInteract.h"

int main()
{
	//����� ��� ������ � ������
	WinInteract mInter;

	//����� ����������� ������
	mInter.Delay(5);

	//��������� ������� �������� pass_rule.txt
	mInter.LoadRules("keys.txt");

	//��������� ��������� ���������� �����
	mInter.LoadLastSave("try.txt");
	
	bool bStop = false;
	while ( !bStop )
	{
		//����������� ������� �� �������
		bStop = mInter.KeyPressDetect();

		//������� ����� � �������
		bStop = bStop||mInter.Process();
	}
}