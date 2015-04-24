#ifndef BACKGROUNDPLANE_H
#define BACKGROUNDPLANE_H

#include "Model.h"
/**
@brief A class representing a BackgroundPlane
It inherits the class Model, and its public methods.
*/
class BackgroundPlane : public Model
{
public:
	/**
	@brief The Default Constructor
	*/
	BackgroundPlane();
	/**
	@brief The Virtual Destructor
	*/
	~BackgroundPlane();
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
	@brief A method to rotate the plane instead.
	This is used on Health UI
	*/
	void setSpin(bool sin){ spin = sin; }

	
private:
	///A boolean containing living status
	bool isAlive;
	///A boolean to decided if object spins
	bool spin;
};

#endif