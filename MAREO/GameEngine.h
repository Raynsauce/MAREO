#pragma once
#include "Main.h"

class Engine {
public:
	Engine()
	{
		puts("[INFO] Engine construct");
		mEvent = new SDL_Event;
		SDL_PollEvent(mEvent);
	}
	~Engine()
	{
		delete mEvent;
	}

	void Update()
	{
		SDL_SetRenderTarget(mainrndr,NULL);
		SDL_RenderCopy(mainrndr,mainTex,NULL,NULL);
		SDL_RenderPresent(mainrndr);

		SDL_SetRenderTarget(mainrndr,mainTex);
		SDL_SetRenderDrawColor(mainrndr,0,0,0,255);
		SDL_RenderClear(mainrndr);
	}
public:
	SDL_Event* mEvent;
};