#include <Logger.h>
#include <SDLApp.h>
#include <GL/gl.h>

int main() {
	Logger::instance().setLoggingLevel(DEBUG);
	
	SDLApp* sdlapp = new SDLApp();
	SDL_Window* w = sdlapp->GetWindow();
	glClearColor(0.8, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(w);
	SDL_Delay(1000);
	delete sdlapp;
}
