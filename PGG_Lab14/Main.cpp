
#include <SDL.h>



#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations

#include "Manager.h"
#include "GameplayState.h"
#include "Titlestate.h"
#include "Time.h"



// An initialisation function, mainly for GLEW
// This will also print to console the version of OpenGL we are using
bool InitGL()
{
	// GLEW has a problem with loading core OpenGL
	// See here: https://www.opengl.org/wiki/OpenGL_Loading_Library
	// The temporary workaround is to enable its 'experimental' features
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr<<"Error: GLEW failed to initialise with message: "<< glewGetErrorString(err) <<std::endl;
		return false;
	}
	std::cout<<"INFO: Using GLEW "<< glewGetString(GLEW_VERSION)<<std::endl;

	std::cout<<"INFO: OpenGL Vendor: "<< glGetString( GL_VENDOR ) << std::endl;
	std::cout<<"INFO: OpenGL Renderer: "<< glGetString( GL_RENDERER ) << std::endl;
	std::cout<<"INFO: OpenGL Version: "<< glGetString( GL_VERSION ) << std::endl;
	std::cout<<"INFO: OpenGL Shading Language Version: "<< glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

	return true;
}


int main(int argc, char *argv[])
{
		// This is our initialisation phase

	// SDL_Init is the main initialisation function for SDL
	// It takes a 'flag' parameter which we use to tell SDL what systems we're going to use
	// Here, we want to use SDL's video system, so we give it the flag for this
	// Incidentally, this also initialises the input event system
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout<<"Whoops! Something went wrong cannot initialise SDL"<<std::endl;
		return -1;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1048);
//	TTF_Init();

	// This is how we set the context profile
	// We need to do this through SDL, so that it can set up the OpenGL drawing context that matches this
	// (of course in reality we have no guarantee this will be available and should provide fallback methods if it's not!)
	// Anyway, we basically first say which version of OpenGL we want to use
	// So let's say 4.3:
	// Major version number (4):
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	// Minor version number (3):
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	// Then we say whether we want the core profile or the compatibility profile
	// Flag options are either: SDL_GL_CONTEXT_PROFILE_CORE   or   SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
	// We'll go for the core profile
	// This means we are using the latest version and cannot use the deprecated functions
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );


	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 480;
	int winHeight = 640;
	SDL_Window *window = SDL_CreateWindow("PGG Assignment 2 - Harry Friend",  // The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);


	//Creates a GameStateManager
	Manager GSManager;


	// The SDL_Renderer is a structure that handles rendering
	SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, 0 );


	// Now that the SDL renderer is created for the window, we can create an OpenGL context for it!
	// This will allow us to actually use OpenGL to draw to the window
	SDL_GLContext glcontext = SDL_GL_CreateContext( window );

	// Call our initialisation function to set up GLEW and print out some GL info to console
	if( !InitGL() )
	{
		return -1;
	}
	

	// We are going to work out how much time passes from frame to frame
	// We will use this variable to store the time at our previous frame
	// This function returns the number of milliseconds since SDL was initialised
	unsigned int lastTime = SDL_GetTicks();


	// Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
	glEnable(GL_DEPTH_TEST);

	Time time;

	time.callStart();

	//Sets GSManagers Game Status to true. 
	GSManager.setGameStatus(true);
	//Adds the GameplayState to the Manager
	GSManager.Add(new Titlestate(&GSManager, renderer));
	GSManager.setMenuStatus(true);
	//GSManager.Add(new GameplayState(&GSManager, renderer));
	bool GameLoop = GSManager.getGameStatus();
	while(GameLoop)
	{
		//Has the manager handle the events of the state on top of the stack.
		GSManager.EventHandle();

		//Updates GameLoop with the current status of the game.
		GameLoop = GSManager.getGameStatus();
		
		
		// Update our world

		time.updateTime();
		float deltaTs = time.getDelta();
		
		//Updates the state on top of the stack.
		GSManager.update(deltaTs);



		// Draw our world

		// Specify the colour to clear the framebuffer to
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		// This writes the above colour to the colour part of the framebuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);
		SDL_RenderClear(renderer);

		//Draws all states.
		GSManager.draw();

		if (GSManager.getMenuStatus())
		{
			SDL_RenderPresent(renderer);
		}
		// This tells the renderer to actually show its contents to the screen
		// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
		if (!GSManager.getMenuStatus())
		{
			SDL_GL_SwapWindow(window);
		}


		// Limiter in case we're running really quick
		if( deltaTs < (1.0f/50.0f) )	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int) (((1.0f/50.0f) - deltaTs)*1000.0f) );
		}
	}

	// If we get outside the main game loop, it means our user has requested we exit


	// Our cleanup phase, hopefully fairly self-explanatory ;)
	SDL_GL_DeleteContext( glcontext );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
