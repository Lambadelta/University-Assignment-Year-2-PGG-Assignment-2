#include "Titlestate.h"
/************************************************************************/
/* This class was submitted as part of PGG Assignment 1 with slight		*/
/*	modifications														*/
/************************************************************************/
Titlestate::Titlestate(Manager* GSManager, SDL_Renderer* renderer) : Gamestate(GSManager, renderer)
{
	Menu = new Background("Assets/images/TitleMenu.png", renderer);
	Title = Mix_LoadMUS("Assets/music/TitleMusic.wav");
	Mix_PlayMusic(Title, -1);
	Mix_VolumeMusic(30);
}

Titlestate::~Titlestate()
{
	delete Menu;
	Mix_FreeMusic(Title);
}

bool Titlestate::EventHandle()
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
				GSManager->setGameStatus(false);
				break;
			case SDLK_RETURN:
				GSManager->setMenuStatus(false);
				GSManager->Change(new GameplayState(GSManager, renderer));
				break;
			case SDLK_h:
				GSManager->Change(new Helpstate(GSManager, renderer));
				break;
			}
		}
	}
	return true;
}

void Titlestate::update(float dt)
{

}

void Titlestate::draw()
{
	SDL_Rect rect = { 0, 0, 480, 640 };
	Menu->callDraw(renderer, Menu->getTexture(), rect, rect);
}
