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
	//�������� iSec ������
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
	//��������� ������� ��������
	m_StrGen.LoadPassRule(pFile);
}

bool WinInteract::KeyPressDetect()
{
	//����������� ������� �� �������
	char cT('_');
	if ( kbhit() )
		cT = getch();

	if ( cT == 27 )
		return true;

	return false;
}

bool WinInteract::Process()
{
	//���������� ��� ������
	
	HWND hWnd=FindWindow("QWidget","�������������� ��������");
	if (hWnd)
	{
		//������� ����� ��������� �����
		ClearTextEdit(hWnd);

		//��������� ������������������
		std::string sTry=m_StrGen.GenNextStr();

		//������� ��������� ������� �� ������
		SendKeyPress(hWnd, sTry);

		//��������� � ������� �� enter �������� ��������
		SendEnterPress(hWnd);

		//���������� ��������� �������� � ���������� �� ������
		ProcessErrorWin(hWnd);

		//��������� ����� ������
		m_iStrLen=sTry.size();

		Sleep(10);

		return false;
	}

	return true;
}

void WinInteract::SendKeyPress(HWND hWnd, const std::string& sTry)
{
	//������� ��������� ������� �� ������
	for (int i=0;i<sTry.size();++i)
	{
		SendMessage( hWnd, WM_KEYDOWN, sTry[i], 0 );
		SendMessage( hWnd, WM_KEYUP, sTry[i], 0 );
	}
}

void WinInteract::SendEnterPress(HWND hWnd)
{
	//��������� � ������� �� enter �������� ��������
	SendMessageTimeout(hWnd, WM_KEYDOWN, 13, 0 ,SMTO_BLOCK, 10,NULL);
	SendMessageTimeout(hWnd, WM_KEYUP, 13, 0 ,SMTO_BLOCK, 10,NULL);
}

void WinInteract::ClearTextEdit(HWND hWnd)
{
	//������� ����� ��������� �����
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
	//���������� ��������� �������� � ���������� �� ������
	for (int i=0;i<100;++i)
	{
		HWND hWndErr=FindWindow("QWidget","������������� ��������� �� �������");
		if (hWndErr)
			SendEnterPress(hWndErr);
		else
			return;
	}
	std::cout<<"\nerror\n";
}