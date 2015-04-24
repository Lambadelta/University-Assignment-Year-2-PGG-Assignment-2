#include "Background.h"

/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/
Background::Background(std::string path, SDL_Renderer* renderer)
{
	BackgroundTexture = NULL;
	loadIMG(path, renderer);
}

Background::~Background()
{
	SDL_DestroyTexture(BackgroundTexture);
}

bool Background::loadIMG(std::string path, SDL_Renderer* renderer)
{
	if (path.empty())
	{
		printf("error");
	}
	SDL_Surface* Temp = NULL;

	Temp = IMG_Load(path.c_str());
	if (Temp == NULL)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cout << "Image -> " << path << "Could not be loaded. Returning NULL" << std::endl;
		SDL_Delay(100);
		SDL_Quit();
		/*Returns the value NULL to the pointer incase of an error with the image*/
		return NULL;
	}
	BackgroundTexture = SDL_CreateTextureFromSurface(renderer, Temp);
	if (BackgroundTexture == NULL)
	{
		return NULL;
	}
	SDL_FreeSurface(Temp);
	return true;
}

SDL_Texture* Background::getTexture()
{
	return BackgroundTexture;
}


SDL_Rect Background::getRect()
{
	return BackRect;
}

bool Background::callDraw(SDL_Renderer* Renderer, SDL_Texture* cTexture, SDL_Rect descRect, SDL_Rect srcRect)
{

	SDL_RenderCopy(Renderer, cTexture, &srcRect, &descRect);
	return true;
}
