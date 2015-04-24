#ifndef TIMER_H
#define TIMER_H

/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/

#include <ctime>
#include <cstdlib>
/**
@brief A class that represents a timer

This class is used to create timers that take in the delta time, and checks if the timer has expired.
*/
class Timer
{
public:
	Timer(){};
	/**
	@brief The timer class object constructor

	Takes in a float parameter to set up the timer.
	@param float - Time for the timer
	*/
	Timer(float);
	/**
	@brief The time class object deconstructor

	Destroys the timer object
	*/
	~Timer();
	/**
	@brief A method for updating the timer

	Takes in the parameter of delta time to update the timer.
	@param float - A float containing the delta time
	*/
	void updateTimer(float);
	/**
	@brief A method for resetting the timer

	*/
	void resetTimer();
	/**
	@brief A method for checking if the time has expired

	Checks if the timer has expired, and returns a true/false.
	@returns bool
	*/

	bool expiredTimer();

	float randNum(int,int);

	void setInitialTime(float);


private:
	 ///A float containing the initial time
	 float initialTime;
	 ///A float containing the current time
	 float currentTime;
};

#endif