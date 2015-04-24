#ifndef TIME_H
#define TIME_H

/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/

#include <SDL.h>
/**
@brief A class that represents time

This class is used to create a time object that is used for update functions/methods.
*/
class Time
{
public:
	/**
	@brief The time class object constructor
	*/
	Time();
	/**
	@brief The time class object deconstructor
	*/
	~Time();
	/**
	@brief A method to call the start of the time class

	Starts the time, and to be used on application initialisation.
	*/
	void callStart();
	/**
	@brief A method to call the time pause

	Pauses the time.
	*/
	void callPause();
	/**
	@brief A method to call the time unpause

	Unpauses the time.
	*/
	void callUnpause();
	/**
	@brief A method to call time stop

	Stops the time completely.
	*/
	void callStop();
	/**
	@brief A method to get the delta time

	Returns a float that contains delta time.
	*/
	float getDelta();
	/**
	@brief A method to update the time

	Called in the application loop to constantly update time.
	@returns float - Containing Delta Time
	*/
	void updateTime();
	/**
	@brief A method to check if the time is paused

	Returns a true/false if the application is paused.
	@returns bool
	*/
	bool isPaused();
	/**
	@brief A method to check if the time has started

	Returns a true/false if the application time is unpaused.
	@returns bool
	*/
	bool isStarted();

private:
	///A float containing the start tick
	float iStartTick;
	///A float containing the pause tick
	float iPausedTick;
	///A float containing the previous tick
	float iLastTick;

	///A float containing the delta time
	float fDelta;
	///A bool containing a true or false to say if the time is paused
	bool bPaused;
	///A bool containing a true or false to say if the time is unpaused
	bool bStart;
};

#endif