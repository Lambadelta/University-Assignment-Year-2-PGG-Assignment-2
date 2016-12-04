#include "Timer.h"
#include <ctime>

/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/
Timer::Timer(float ms)
{
	if (ms < 0)
	{
		initialTime = 0;
	}
	else
	{
		initialTime = ms;
	}

	currentTime = initialTime;

}
Timer::~Timer()
{

}

void Timer::updateTimer(float DeltaTime)
{
	if (currentTime > 0)
	{
		currentTime -= DeltaTime;
	}

}
void Timer::resetTimer()
{
	currentTime = initialTime;
}
bool Timer::expiredTimer()
{
	if (currentTime <= 0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}


float Timer::randNum(int min, int max)
{
	std::srand((unsigned int) std::time_t(0));
	int random = std::rand() % (max - min) + min;
	return (float)random;
}

void Timer::setInitialTime(float ms)
{
	if (ms < 0)
	{
		initialTime = 0;
	}
	else
	{
		initialTime = ms;
	}

	currentTime = initialTime;
}
