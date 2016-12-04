#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "Gamestate.h"
#include "Manager.h"
#include "Background.h"
#include "GameplayState.h"
#include "Titlestate.h"
#include <SDL_ttf.h>

class Creditsstate : public Gamestate
{
public:
	Creditsstate(Manager*, SDL_Renderer*, int&);
	~Creditsstate();


	bool EventHandle();
	void update(float);
	void draw();

private:

	Background* Credits;
	Mix_Music* GameOver;
	int score;
	TTF_Font* Font;

};
#endif