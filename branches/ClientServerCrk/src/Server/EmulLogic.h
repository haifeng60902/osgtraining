#ifndef _EMUL_LOGIC_H_
#define _EMUL_LOGIC_H_

class EmulLogic
{
public:
	EmulLogic();
	~EmulLogic();

	//������ ����� ���������� �������
	void Accumulate(const char* pBuff, int iSize);

	//���������� ������� ������
	void Process();

	//��������� ��� �������� � ����
	const char* GetResult(int *pSize);

private:
	//����� ��� ������ ���������
	char inBuff[32768];
	int inSize;

	//���������
	char outBuff[32768];
	int outSize;
};

#endif	//_EMUL_LOGIC_H_