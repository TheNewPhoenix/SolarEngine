#include "Input.h"

#include <SDL.h>

namespace solar 
{

	Input::Input(Context* context) :
		Object(context)
	{
	}

	Input::~Input()
	{
	}

	void Input::update()
	{
		SDL_Event evt;
		while (SDL_PollEvent(&evt))
			handleSDLEvent(&evt);
	}

	void Input::handleSDLEvent(void* sdlEvent)
	{
		SDL_Event& evt = *static_cast<SDL_Event*>(sdlEvent);

		switch (evt.type)
		{
		case SDL_QUIT:
			sendEvent("windowclosed");
			break;

		default: break;
		}
	}

}