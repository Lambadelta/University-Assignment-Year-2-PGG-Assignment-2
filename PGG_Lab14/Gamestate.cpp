#include "GameplayState.h"
/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/
Gamestate::Gamestate(Manager* GSManager, SDL_Renderer* renderer)
{
	this->GSManager = GSManager;
	this->renderer = renderer;
}

