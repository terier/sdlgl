#ifndef EVENT_RECEIVER_H_INCL
#define EVENT_RECEIVER_H_INCL

#include <SDL2/SDL.h>

class EventReceiver {

public:

	EventReceiver();
	virtual ~EventReceiver();

	virtual void OnEvent(const SDL_Event& event);

protected:

};

#endif