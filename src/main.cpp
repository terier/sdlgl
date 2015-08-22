#include <Logger.h>
#include <SDLApp.h>
#include <GL/gl.h>
#include <Globals.h>
#include <chrono>

using namespace std::chrono;
#define HRC high_resolution_clock

int main() {
	Logger::instance().setLoggingLevel(DEBUG);
	
	SDLApp* sdlapp = new SDLApp();
	SDL_Window* window = sdlapp->GetWindow();

	Globals["running"] = "true";

	HRC::time_point prevTime = HRC::now();
	HRC::time_point currTime = HRC::now();
	HRC::time_point strtTime = HRC::now();
	while (Globals["running"] == "true") {
		currTime = HRC::now();
		double dt = duration_cast<duration<double>>(currTime - prevTime).count();
		double t = duration_cast<duration<double>>(currTime - strtTime).count();

		LOG(TRACE, "Main loop");

		sdlapp->ProcessEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		float x = 10.f * sin(t);

		glBegin(GL_TRIANGLES);
		glColor3f(0,0,1);
		glVertex2f(0, 0);
		glVertex2f(x, 100);
		glVertex2f(50, 90);
		glEnd();

		SDL_GL_SwapWindow(window);

		prevTime = currTime;
	}
	delete sdlapp;
}
