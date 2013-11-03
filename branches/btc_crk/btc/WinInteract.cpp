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
	//m_StrGen.LoadPassRule(pFile);
	m_StrDecode.LoadTable(pFile);
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

std::string WinInteract::GenNextStr()
{
	//��� �������
	//return m_StrGen.GenNextStr();
	return m_StrDecode.GenNextStr();
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
		//std::string sTry=m_StrGen.GenNextStr();
		std::string sTry=m_StrDecode.GenNextStr();

		if(!sTry.empty())
			std::cout<<sTry<<" ";
		else
			std::cout<<"\nThe End\n";

		//������� ��������� ������� �� ������
		SendKeyPress(hWnd, sTry);

		Sleep(200);

		//��������� � ������� �� enter �������� ��������
		SendEnterPress(hWnd);

		//���������� ��������� �������� � ���������� �� ������
		ProcessErrorWin();

		//��������� ����� ������
		m_iStrLen=sTry.size();

		return false;
	}

	return true;
}

void WinInteract::SendKeyPress(HWND hWnd, const std::string& sTry)
{
	//������� ��������� ������� �� ������
	for (int i=0;i<sTry.size();++i)
	{
		SendMessage( hWnd, WM_CHAR, sTry[i], 0 );
		//SendMessage( hWnd, WM_KEYUP, sTry[i], 0 );
	}
}

void WinInteract::SendEnterPress(HWND hWnd)
{
	//��������� � ������� �� enter �������� ��������
	SendMessageTimeout(hWnd, WM_KEYDOWN, 13, 0 ,SMTO_BLOCK, 100,NULL);
	SendMessageTimeout(hWnd, WM_KEYUP, 13, 0 ,SMTO_BLOCK, 200,NULL);
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
		Sleep(10);
	}
}

void WinInteract::ProcessErrorWin()
{
	//���������� ��������� �������� � ���������� �� ������
	for (int i=0;i<10;++i)
	{
		HWND hWnd=FindWindow("QWidget","�������������� ��������");
		if (hWnd)
		{
			HWND hWndErr=FindWindow("QWidget","������������� ��������� �� �������");
			if (hWndErr)
			{
				ClearTextEdit(hWnd);

				//������� ��������� ������� �� ������
				SendEnterPress(hWndErr);
			}
			else
			{
				return;
			}
		}

		//std::cout<<"\nh:"<<hWnd;
		Sleep(10);
	}

	//��������� � ���� ������� ������
	//m_StrGen.SaveResult();
	exit(1);
}

void WinInteract::SaveStr()
{
	//��������� ������� ���������
	//m_StrGen.SaveResult();
}

void WinInteract::LoadLastSave(const char* pFile)
{
	//��������� ��������� ���������� �����
	//m_StrGen.LoadLastSave(pFile);
	m_StrDecode.LoadLastSave(pFile);
}