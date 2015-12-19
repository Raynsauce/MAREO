#pragma once
#include "Main.h"
#include "Player.h"

class Engine {	//Engine is to be implemented further
public:
	Engine() : mEvent(new SDL_Event)
	{
		puts("[INFO] Engine construct");
		SDL_PollEvent(mEvent);
		SetState(INTRO);
	}
	~Engine()
	{
		puts("[INFO] Engine destruct");
		delete mEvent;
	}

	const enum eState { SPLASH, INTRO, MAINMENU, LEVELS, PLAYING };
	
	inline void SetState(const int& nState)		{ cState = static_cast<eState>(nState); }
	inline void SetState(const eState& nState)  { cState = nState; }
	inline eState GetState(void)				{ return cState; }

	inline void Update()
	{
		switch(cState){
		case SPLASH:	//"Nintendo" splash screen

			break;
		case INTRO:	//Intro code
			
			break;
		case MAINMENU: //"Start"/"File select" screen
			
			break;
		case LEVELS: //Level select
			
			break;
		case PLAYING: //User has control of Player
			
			break;
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