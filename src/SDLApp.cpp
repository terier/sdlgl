#include <SDLApp.h>
#include <Logger.h>
#include <Globals.h>
#include <GL/gl.h>

#include <sstream>

bool SDLApp::isInit = false;

SDLApp::SDLApp()
	: window(NULL),
	  glcontext(NULL),
	  eventReceiver(NULL)
{
	// Initialize SDL
	if (!isInit) {
		LOG(DEBUG, "Initializing SDL");
		if (SDL_Init(SDL_INIT_VIDEO)) {
			LOG(ERROR, SDL_GetError());
		} else {
			isInit = true;
		}
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Create the base window
	LOG(DEBUG, "Creating window");
	window = SDL_CreateWindow(
		"Graphics",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!window) {
		LOG(ERROR, SDL_GetError());
	}

	// Create an OpenGL context within the base window
	LOG(DEBUG, "Creating OpenGL context");
	glcontext = SDL_GL_CreateContext(window);
	if (!glcontext) {
		LOG(ERROR, SDL_GetError());
	} else {
		int major = 0;
		int minor = 0;
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
		std::ostringstream ss;
		ss << "OpenGL version: " << major << "." << minor;
		LOG(INFO, ss.str());

		InitGL();
	}
}

SDLApp::~SDLApp() {
	if (window) {
		LOG(DEBUG, "Destroying window");
		SDL_DestroyWindow(window);
	}
	if (glcontext) {
		LOG(DEBUG, "Deleting OpenGL context");
		SDL_GL_DeleteContext(glcontext);
	}
	LOG(DEBUG, "Quitting SDL");
	SDL_Quit();
	isInit = false;
}

void SDLApp::InitGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

SDL_Window* SDLApp::GetWindow() const {
	return window;
}

SDL_GLContext SDLApp::GetGLContext() const {
	return glcontext;
}

EventReceiver* SDLApp::GetEventReceiver() const {
	return eventReceiver;
}

bool SDLApp::IsInitialized() const {
	return isInit;
}

void SDLApp::ProcessEvents() {
	SDL_Event event;
	if (eventReceiver) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				Globals["running"] = "false";
			}
			eventReceiver->OnEvent(event);
		}
	} else {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				Globals["running"] = "false";
			}
		}
	}
}