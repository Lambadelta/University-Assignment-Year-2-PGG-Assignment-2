#ifndef HELPSTATE_H
#define HELPSTATE_H

#include "Gamestate.h"
#include "Manager.h"
#include "Background.h"
#include "Titlestate.h"
/************************************************************************/
/* This class was submitted as part of PGG Assignment 1 with slight		*/
/*	modifications														*/
/************************************************************************/
class Helpstate : public Gamestate
{
public:
	Helpstate(Manager*, SDL_Renderer*);
	~Helpstate();


	bool EventHandle();
	void update(float);
	void draw();

private:

	Background* Help;

};
#endif