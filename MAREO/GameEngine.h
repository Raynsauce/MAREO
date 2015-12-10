#pragma once
#include "Main.h"
#include "Player.h"

class Engine {	//Engine is to be implemented further
public:
	Engine() : mEvent(new SDL_Event)
	{
		puts("[INFO] Engine construct");
		SDL_PollEvent(mEvent);
		SetEState(INTRO);
	}
	~Engine()
	{
		delete mEvent;
	}

	const enum eState { INTRO, MAINMENU, LEVELS, PLAYING };
	
	inline void SetEState(const int& nState)	 { cState = static_cast<eState>(nState); }
	inline void SetEState(const eState& nState){ cState = nState; }
	inline eState SetEState(void)				 { return cState; }

	void Update()
	{
		switch(cState)
		{
		case INTRO:
			//Intro code
			break;
		case MAINMENU: break;
		case LEVELS: break;
		case PLAYING: break;
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