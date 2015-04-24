#ifndef MANAGER_H
#define MANAGER_H

#include "Gamestate.h"
#include <iostream>
#include <vector>
/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/


/**
@brief A class to manage the gamestate system.

This class allows the ability to add, remove, change different gamestates.
It manages their updating, and drawing abilities as needed.
*/
class Manager
{
public:
	/**
	@brief The Manager deconstructor. Handles destroying the gamestates.
	*/
	~Manager();

	/**
	@brief This method takes in a pointer to a gamestate, and adds it to the gamestate vector.

	@param Gamestate* - A pointer to a gamestate.
	*/
	void Add(Gamestate*);
	/**
	@brief This method takes in a pointer to a gamestate, and changes the current state to the new one.

	Deletes all other gamestates in the vector.

	@param Gamestate* - A pointer to a gamestate.
	*/
	void Change(Gamestate*);
	/**
	@brief This method removes the most recently added gamestate.

	*/
	void RemoveLast();
	/**
	@brief This method returns the current top gamestate's event handler so only that state is recieving events.

	@returns bool - returns the current active gamestate's event handler.
	*/
	bool EventHandle();
	/**
	@brief This method takes in deltatime, and updates the current active gamestate.

	@param float dt - A float containing delta time. Used for updating other methods/functions.
	*/
	void update(float);
	/**
	@brief This method goes through all gamestates inside the vGS vector, and draws them.

	*/
	void draw();

	bool getGameStatus() { return endGame; };
	void setGameStatus(bool status) { endGame = status; };

	bool getMenuStatus() { return isMenu; };
	void setMenuStatus(bool status) { isMenu = status; };
private:
	/**
	@brief A vector containing all gamestates.
	*/
	std::vector<Gamestate*> vGS;

	bool endGame;
	bool isMenu;
};

#endif