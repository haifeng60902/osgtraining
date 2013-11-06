#include "Time/Timer.h"

Timer::Timer()
{
	__int64 ifreq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&ifreq);
	dFreq=ifreq;
}

Timer::~Timer()
{

}

float Timer::GetTime()
{
	__int64 it;
	QueryPerformanceCounter((LARGE_INTEGER*)&it);
	double dIt=it;

	return dIt/dFreq;
}