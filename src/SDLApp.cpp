#include <SDLApp.h>
#include <Logger.h>

#include <sstream>

bool SDLApp::isInit = false;

SDLApp::SDLApp()
	: window(NULL),
	  glcontext(NULL)
{
	if (!isInit) {
		LOG(DEBUG, "Initializing SDL");
		if (SDL_Init(SDL_INIT_VIDEO)) {
			LOG(ERROR, SDL_GetError());
		} else {
			isInit = true;
		}
	}
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

SDL_Window* SDLApp::GetWindow() const {
	return window;
}

SDL_GLContext SDLApp::GetGLContext() const {
	return glcontext;
}

bool SDLApp::IsInit() const {
	return isInit;
}