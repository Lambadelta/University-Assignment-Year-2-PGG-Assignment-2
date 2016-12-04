#include "Helpstate.h"
/************************************************************************/
/* This class was submitted as part of PGG Assignment 1 with slight		*/
/*	modifications														*/
/************************************************************************/
Helpstate::Helpstate(Manager* GSManager, SDL_Renderer* renderer) : Gamestate(GSManager,renderer)
{
	Help = new Background("Assets/images/Help.png", renderer);
}

Helpstate::~Helpstate()
{
	delete Help;
}

bool Helpstate::EventHandle()
{
	SDL_Event eve;
	while (SDL_PollEvent(&eve))
	{
		switch (eve.type)
		{
		case SDL_QUIT:
			GSManager->setGameStatus(false);
			break;
		case SDL_KEYDOWN:
			switch (eve.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				GSManager->Change(new Titlestate(GSManager, renderer));
				break;
			}
		}
	}
	return true;
}

void Helpstate::update(float)
{

}

void Helpstate::draw()
{
	SDL_Rect rect = { 0, 0, 480, 640 };
	Help->callDraw(renderer, Help->getTexture(), rect, rect);
}
