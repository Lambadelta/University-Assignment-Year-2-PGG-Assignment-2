#ifndef BULLET_H
#define BULLET_H

#include "Model.h"
/**
@brief A class representing a Bullet
It inherits the class Model, and its public methods.
*/
class Bullet : public Model
{
public:
	/**
	@brief The Default Constructor
	*/
	Bullet();
	/**
	@brief The Virtual Destructor
	*/
	~Bullet();
	/**
	@brief A method to update variables using a float
	@param float dt - A float containing deltatime
	*/
	void update(float);
	/**
	@brief A method to set the Alive status of the Entity
	@param bool - A bool containing the new status
	*/
	void setAliveStatus(bool status){ isAlive = status; };
	/**
	@brief A method to get the Alive status of the Entity
	@returns bool - A bool containing the current status
	*/
	bool getAliveStatus(){ return isAlive; };
	/**
	@brief A method to tell if bullet is heading downwards, or updates
	@param bool - A boolean containing the new status
	*/
	void upordown(bool ud){ UporDown = ud; }
private:

	///A boolean containing living status
	bool isAlive;
	///Static float containing velocity
	static float fVelocity;

	///true for up, false for down
	bool UporDown;
};



#endif