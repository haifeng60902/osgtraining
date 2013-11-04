#ifndef _EMUL_LOGIC_H_
#define _EMUL_LOGIC_H_

class EmulLogic
{
public:
	EmulLogic();
	~EmulLogic();

	//данные могут приниматся частями
	void Accumulate(const char* pBuff, int iSize);

	//обработать входные данные
	void Process();

	//результат для отправки в сеть
	const char* GetResult(int *pSize);

private:
	//буфер для приема сообщений
	char inBuff[32768];
	int inSize;

	//результат
	char outBuff[32768];
	int outSize;
};

#endif	//_EMUL_LOGIC_H_