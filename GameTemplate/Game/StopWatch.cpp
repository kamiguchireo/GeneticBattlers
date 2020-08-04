#include "stdafx.h"
#include "StopWatch.h"

//åvë™èIóπ
void StopWatch::Stop()
{
	::QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	::QueryPerformanceCounter((LARGE_INTEGER*)&end);
	elapsed = double(end - begin) / freq;
	elapsedMill = elapsed * 1000.0;
	elapsedMicro = elapsedMill * 1000.0;
}