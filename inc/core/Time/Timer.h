#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>

class Timer
{
public:
	Timer();
	~Timer();

	float GetTime();

private:
	double dFreq;
};

#endif	//_TIMER_H_