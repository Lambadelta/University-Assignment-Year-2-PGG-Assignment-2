#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <iostream>
/************************************************************************/
/* This class was submitted as part of PGG Assignment 1                 */
/************************************************************************/

/**
@brief A class that represents a background

This class is used to create a background object
*/
class Background
{
public:
	Background(std::string, SDL_Renderer*);
	~Background();
	/**
	@brief A method to get the background surface

	@Returns SDL_Surface*  - A pointer to its surface.
	*/
	SDL_Surface* getSurface();
	/**
	@brief A method for creating a texture from the surface.

	@Returns bool - True if success, or false if failed.
	*/
	bool loadIMG(std::string, SDL_Renderer*);
	/**
	@brief A method to get the background texture

	@Returns SDL_Texture* - A pointer to its texture.
	*/
	SDL_Texture* getTexture();
	/**
	@brief A method to draw the background

	@param SDL_Renderer* - A pointer to the renderer.
	@param SDL_Texture* - A pointer to the texture to be drawn.
	@param SDL_Rect - A destination Rect for its location on the screen.
	@param SDL_Rect - A Source Rect for its location on the sprite.

	@Returns bool - True if success, or false if failed.
	*/
	bool callDraw(SDL_Renderer*, SDL_Texture*,SDL_Rect, SDL_Rect);

	/**
	@brief A method to get the background Rect

	@Returns a SDL_Rect when called.
	*/
	SDL_Rect getRect();

private:
	///A SDL_Texture* containing the background texture
	SDL_Texture* BackgroundTexture;
	///A SDL_Rect containing the background Rect
	SDL_Rect BackRect;
};


#endif