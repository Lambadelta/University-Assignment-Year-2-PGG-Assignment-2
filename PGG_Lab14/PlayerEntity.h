#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include "Model.h"
#include "Bullet.h"
#include "Timer.h"
#include <vector>
/**
@brief A class representing a Player Entity
It inherits the class Model, and its public methods.
*/
class PlayerEntity : public Model
{
public:
	/**
	@brief The Default Constructor
	*/
	PlayerEntity();
	/**
	@brief The Default Destructor
	*/
	~PlayerEntity();
	/**
	@brief A method to update variables using a float
	@param float dt - A float containing deltatime
	*/
	void update(float);
	/**
	@brief A method to shoot bullets. 
	When called by the user it adds a new bullet to the vector.
	*/
	void shootBullet();
	/**
	@brief A method to move left.
	It works by setting a boolean called moveLeft to true, which updates in update method
	@param bool 
	*/
	void movePLeft(bool b){ moveLeft = b; };
	/**
	@brief A method to move Right.
	It works by setting a boolean called moveRight to true, which updates in update method
	@param bool
	*/
	void movePRight(bool b){ moveRight = b; };
	/**
	@brief A method to set the bulletMesh to the Mesh loaded in by the Object Loader for creation of future bullets
	@param Object - An object containing the bullet mesh
	*/
	void setBulletMesh(Object bmesh) { bulletMesh = bmesh; }
	/**
	@brief A method to get the vector storing the bullets
	@returns std::vector<Bullet> - A reference to a vector of bullets
	*/
	std::vector<Bullet>& getVBullet(){	return vBullet;};
	/**
	@brief A method to set the Alive status of the Entity
	@param bool - A boolean containing the new status
	*/
	void setAliveStatus(bool status){ isAlive = status; };
	/**
	@brief A method to get the Alive status of the Entity
	@returns bool - A boolean containing the current status
	*/
	bool getAliveStatus(){ return isAlive; };
	/**
	@brief A method to subtract lives from the entity
	@param int - A number to subtract by
	*/
	void subLives(int sub){ Lives -= sub; }
	/**
	@brief A method to get lives from the entity
	@returns int - An int containing the current life of the entity
	*/
	int getLives(){ return Lives; }
private:

	///A boolean to move left
	bool moveLeft;
	///A boolean to move right
	bool moveRight;
	///A boolean to check if entity is alive
	bool isAlive;
	///A int to store the entities lives
	int Lives;
	///Static float to set Player's Movement Speed
	static float fPlayerSpeed;
	///Static float to set the Player's Rotation Speed
	static float fRotateSpeed;
	///Static float to set the Player's Maximum Rotation
	static float fRotationMax;
	///A timer for bullets
	Timer bTimer;
	///A std::vector containing bullets
	std::vector<Bullet>vBullet;
	///A Object containing the mesh data of a bullet
	Object bulletMesh;
};

#endif