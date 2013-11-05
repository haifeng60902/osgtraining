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

	//результат для отправки
	const char* GetResult(int* pSize);

	//получить ответ от сервера
	void Accumulate(TCPStream* stream);

	//обработать входные данные
	void Process();

private:

	//заполнить выходной буфер
	void FillOutBuffer(int i);

	//буфер для приема сообщений
	char inBuff[32768];
	char inBuffTmp[32768];
	int inSize;

	//результат
	char outBuff[32768];
	int outSize;

	std::string sNode;
};

#endif	//_EMUL_LOGIC_H_