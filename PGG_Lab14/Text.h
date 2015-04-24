#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

/************************************************************************/
/* Was submitted as part of PGG Assignment 1                            */
/************************************************************************/
class Text
{
public:
	Text();
	~Text();
	
	bool create(std::string, SDL_Renderer*);
	void callDraw(SDL_Renderer*);
	void setRect(SDL_Rect);
	SDL_Rect getRect() { return descRect; };
	int getWidth() { return width; };
	int getHeight() { return height; };
private:

	SDL_Texture* textTexture;
	TTF_Font* font;
	int width;
	int height;
	SDL_Rect descRect;
};

#endif