#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include "Model.h"
#include "Bullet.h"
#include "Timer.h"
#include <vector>
/**
@brief A class representing a Enemy Entity
It inherits the class Model, and its public methods.
*/
class EnemyEntity : public Model
{
public:
	/**
	@brief The Default Constructor
	*/
	EnemyEntity();
	/**
	@brief The Virtual Destructor
	*/
	~EnemyEntity();
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
	@brief A method to fire bullets.
	Uses a timer to decided when to shoot.
	*/
	void shootBullet();
	/**
	@brief A method to update the Bullet Object Mesh
	@param Object - An object containing the mesh data
	*/
	void setBulletMesh(Object bmesh) { bulletMesh = bmesh; }
	/**
	@brief A method to decided if it will go off the screen Left oro Right
	*/
	void setExit(){
		if (Position.x < 0.f){ exitLeftorRight = true; }
		else if (Position.x > 0.f){ exitLeftorRight = false; }
	};
	/**
	@brief A method to get the vector storing the bullets
	@returns std::vector<Bullet> - A reference to a vector of bullets
	*/
	std::vector<Bullet>& getVBullet(){ return vBullet; };
private:
	///A boolean containing Alive status
	bool isAlive;
	///A static float containing velocity
	static float fVelocity;
	///A static float containing Max Rotation
	static float fRotationMax;
	///true for left, false for right
	bool exitLeftorRight;
	///A object to store bullet mesh
	Object bulletMesh;
	///A timer for calling shootBullet
	Timer Shoot;
	///A vector of bullets
	std::vector<Bullet> vBullet;
};

#endif