#ifndef SDLAPP_H_INCL
#define SDLAPP_H_INCL

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class SDLApp {

	static bool isInit;

	SDL_Window* window;
	SDL_GLContext glcontext;

public:

	SDLApp();
	~SDLApp();

	SDL_Window* GetWindow() const;
	SDL_GLContext GetGLContext() const;
	bool IsInit() const;

};

#endif