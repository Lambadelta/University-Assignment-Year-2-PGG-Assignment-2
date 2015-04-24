#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>
#include <string>

/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/

class Manager;

class Gamestate
{
public:
	Gamestate(Manager*, SDL_Renderer*);
	virtual ~Gamestate() {};

	virtual bool EventHandle() = 0;
	virtual void update(float) = 0;
	virtual void draw() = 0;

	std::string getname() {return Name;}
protected:

	Manager* GSManager;
	SDL_Renderer* renderer;
	std::string Name;
};

#endif