#ifndef _BIN_INPUT_H_
#define _BIN_INPUT_H_

#include <string>
#include <vector>

struct binInput
{
	binInput():runTime(600),
		statusTime(60),
		restoreTime(30),
		passFile("pass.txt")
	{};
	std::string exeFile;				//��� exe �����
	std::string hashFile;				//��� ����� � ������
	std::string passFile;	//�������� ���� � ��������
	int runTime;					//����� � �������� �� ������
	int statusTime;					//�������� ������ ����� ������ (���)
	int restoreTime;					//��������� ������ ������ (���)
};

typedef std::vector<std::string> tVecStr;

#endif	//_BIN_INPUT_H_