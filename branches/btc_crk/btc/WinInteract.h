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

	//�������� iSec ������
	void Delay(int iSec);

	//��������� ������� ��������
	void LoadRules(const char* pFile);

	//��������� ��������� ���������� �����
	void LoadLastSave(const char* pFile);

	//��������� ��������� ���������� �����
	void LoadEncode(const char* pFile);

	//����������� ������� �� �������
	bool KeyPressDetect();

	//���������� ��� ������
	bool Process();

	//��� �������
	std::string GenNextStr();

	//��������� ������� ���������
	void SaveStr();
private:

	//������� ��������� ������� �� ������
	void SendKeyPress(HWND hWnd, const std::string& sTry);

	//��������� � ������� �� enter �������� ��������
	void SendEnterPress(HWND hWnd);

	//������� ����� ��������� �����
	void ClearTextEdit(HWND hWnd);

	//���������� ��������� �������� � ���������� �� ������
	void ProcessErrorWin();

	//��������� �����
	StrGen m_StrGen;

	//������� ����� ��������
	StrDecode m_StrDecode;

	//����� ���������� ������, ������� ����� ������� 
	int m_iStrLen;
};

#endif	//_WIN_INTERACT_H_