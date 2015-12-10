#pragma once
#include "Main.h"
#include "Player.h"

class Engine {	//Engine is to be implemented further
public:
	Engine() : mEvent(new SDL_Event)
	{
		puts("[INFO] Engine construct");
		SDL_PollEvent(mEvent);
		SetPState(INTRO);
	}
	~Engine()
	{
		delete mEvent;
	}

	const enum eState {
		INTRO,
		MAINMENU,
		LEVELS,
		PLAYING
	};
	
	inline void SetPState(const int& newState)	 { cState = static_cast<eState>(newState); }
	inline void SetPState(const eState& newState){ cState = newState; }
	inline eState GetPState(void)				 { return cState; }

	void Update()
	{
		switch(cState)
		{
		case Engine::INTRO:

			break;
		case Engine::MAINMENU: break;
		case Engine::LEVELS: break;
		case Engine::PLAYING: break;
		default: break;
		}

		SDL_SetRenderTarget(mainrndr,NULL);
		SDL_RenderCopy(mainrndr,mainTex,NULL,NULL);
		SDL_RenderPresent(mainrndr);

		SDL_SetRenderTarget(mainrndr,mainTex);
		SDL_SetRenderDrawColor(mainrndr,0,0,0,255);
		SDL_RenderClear(mainrndr);
	}
public:
	SDL_Event* mEvent;
private:
	eState cState;
};