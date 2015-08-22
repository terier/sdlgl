#ifndef SDLAPP_H_INCL
#define SDLAPP_H_INCL

#include <SDL2/SDL.h>
#include <EventReceiver.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class SDLApp {

public:

	SDLApp();
	~SDLApp();

	void InitGL();

	SDL_Window* GetWindow() const;
	SDL_GLContext GetGLContext() const;
	EventReceiver* GetEventReceiver() const;
	bool IsInitialized() const;

	void ProcessEvents();

private:

	static bool isInit;

	SDL_Window* window;
	SDL_GLContext glcontext;

	EventReceiver* eventReceiver;

};

#endif