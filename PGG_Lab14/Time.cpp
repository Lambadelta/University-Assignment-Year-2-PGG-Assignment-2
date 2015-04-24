#include "Time.h"
/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/
Time::Time()
{
	iStartTick = 0;
	iPausedTick = 0;
	iLastTick = 0;

	bPaused = false;
	bStart = false;
}
Time::~Time()
{

}

void Time::callStart()
{
	bStart = true;
	bPaused = false;

	iStartTick = (float)SDL_GetTicks();
	iPausedTick = 0;

}
void Time::callPause()
{
	if (bStart == true && bPaused == false)
	{
		bPaused = true;

		iPausedTick = (float)SDL_GetTicks() - iStartTick;
		iStartTick = 0;
	}
}

void Time::callUnpause()
{
	if (bStart == false && bPaused == true)
	{
		bPaused = false;

		iStartTick = (float)SDL_GetTicks() - iStartTick;
		iPausedTick = 0;
	}
}

void Time::callStop()
{

}


float Time::getDelta()
{
	return (fDelta);
}

void Time::updateTime()
{
	if (bStart == true)
	{
		if (bPaused == true)
		{
			iLastTick = iPausedTick;
			fDelta = (iPausedTick - iLastTick);
		}
		else
		{
			
			iStartTick = (float)SDL_GetTicks();
			fDelta = (float) (iStartTick - iLastTick) /1000.f;
			iLastTick = iStartTick;
		}
	}

}

bool Time::isPaused()
{
	return bPaused;
}

bool Time::isStarted()
{
	return bStart;
}

/*16.7 Mil Seconds = 60 fps use SDL_Delay*/