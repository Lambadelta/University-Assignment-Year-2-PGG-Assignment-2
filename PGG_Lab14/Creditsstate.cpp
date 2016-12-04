#include "Creditsstate.h"

Creditsstate::Creditsstate(Manager*GSManager, SDL_Renderer* renderer, int& s) : Gamestate(GSManager, renderer)
{
	Credits = new Background("Assets/images/Credits.png", renderer);

	score = s;
	Font = NULL;
	GameOver = Mix_LoadMUS("Assets/music/gameOver.wav");
	Mix_PlayMusic(GameOver, -1);
}

Creditsstate::~Creditsstate()
{
	delete Credits;
}

bool Creditsstate::EventHandle()
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

void Creditsstate::update(float dt)
{

}

void Creditsstate::draw()
{
	SDL_Rect rect = { 0, 0, 480, 640 };
	Credits->callDraw(renderer, Credits->getTexture(), rect, rect);
}
