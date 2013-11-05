#ifndef _EMUL_LOGIC_H_
#define _EMUL_LOGIC_H_

#include <string>

class TCPStream;
class EmulLogic
{
public:
	EmulLogic();
	~EmulLogic();

	void Init(const std::string& sNode);

	//��������� ��� ��������
	const char* GetResult(int* pSize);

	//�������� ����� �� �������
	void Accumulate(TCPStream* stream);

	//���������� ������� ������
	void Process();

private:

	//��������� �������� �����
	void FillOutBuffer(int i);

	//����� ��� ������ ���������
	char inBuff[32768];
	char inBuffTmp[32768];
	int inSize;

	//���������
	char outBuff[32768];
	int outSize;

	std::string sNode;
};

#endif	//_EMUL_LOGIC_H_