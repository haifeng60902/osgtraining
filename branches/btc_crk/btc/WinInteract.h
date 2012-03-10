#ifndef _WIN_INTERACT_H_
#define _WIN_INTERACT_H_

#include <Windows.h>

#include "StrGen.h"

class WinInteract
{
public:
	WinInteract();
	~WinInteract();

	//�������� iSec ������
	void Delay(int iSec);

	//��������� ������� ��������
	void LoadRules(const char* pFile);

	//��������� ��������� ���������� �����
	void LoadLastSave(const char* pFile);

	//����������� ������� �� �������
	bool KeyPressDetect();

	//���������� ��� ������
	bool Process();
private:

	//������� ��������� ������� �� ������
	void SendKeyPress(HWND hWnd, const std::string& sTry);

	//��������� � ������� �� enter �������� ��������
	void SendEnterPress(HWND hWnd);

	//������� ����� ��������� �����
	void ClearTextEdit(HWND hWnd);

	//���������� ��������� �������� � ���������� �� ������
	void ProcessErrorWin(HWND hWnd);

	//��������� �����
	StrGen m_StrGen;

	//����� ���������� ������, ������� ����� ������� 
	int m_iStrLen;
};

#endif	//_WIN_INTERACT_H_