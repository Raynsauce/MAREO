#pragma once
#include "stdafx.h"
#include "Main.h"
#include "GameEngine.h"

class Entity {
protected:
	struct Dir {
		bool movul;	///move up,  left
		bool movdr; ///move down,right
	};
};

class Camera : protected Entity {
public:
	Camera(){
		puts("[INFO] Camera object construct");
		cProps = new SDL_Rect;
	}
	~Camera(){
		delete cProps;
	}

protected:
	SDL_Rect* cProps;
};

class Player : protected Camera {	//Engine is to be implemented further
public:
	Player()
	{
		puts("[INFO] Player object construct");
		rndrRect =	new SDL_Rect;
		*rndrRect = {(WIDTH/2),(HEIGHT/2),WIDTH,HEIGHT};			//Defined starting position

		dirx = {};
		diry = {};
		
		Vel = Run();
		Sprinting = false;

		s_stand = IMG_LoadTexture(mainrndr,"assets\\mario\\s_stand.png");
		s_run0 = IMG_LoadTexture(mainrndr,"assets\\mario\\s_run0.png");
		s_run1 = IMG_LoadTexture(mainrndr,"assets\\mario\\s_run1.png");
		if( SDL_QueryTexture(s_stand,nullptr,nullptr,&(rndrRect->w),&(rndrRect->h)) )	//If QueryTexture failed, print an error
		{ std::cerr << "[ERR] QueryTexture FAILED: " << SDL_GetError() << std::endl; }
		
		*Camera::cProps = *rndrRect;	//set the value of cProps instead of pointer address


		SetPState(STAND | ALIVE);
		std::cout << ((STAND|ALIVE)) << std::endl;
	}
	~Player()
	{
		puts("[INFO] Player object destruct");
		delete rndrRect;
		SDL_DestroyTexture(s_stand);
		SDL_DestroyTexture(s_run0);
		SDL_DestroyTexture(s_run1);
	}
	
	inline void Update(SDL_KeyboardEvent& key,SDL_MouseButtonEvent& mouse)
	{
		PlayerKeyMoves(key,mouse);

		SDL_SetRenderDrawColor(mainrndr,255,0,255,255);
		SDL_RenderDrawRects(mainrndr,rndrRect,1);
		
		SDL_SetRenderTarget(mainrndr,mainTex);
		SDL_RenderCopy(mainrndr,s_stand,NULL,rndrRect);
	}

	const enum {		//6 types of states -> 6 hex places
		STAND		= 0x000001, //different types of states don't interfere (in theory)
		MOVE		= 0x000002,
		STOP		= 0x000004,
		THING		= 0x000008,
		
		WALK		= 0x000010,
		RUN			= 0x000020, //Movement
		SPRINT		= 0x000030,
		TURN		= 0x000040,
		JUMP		= 0x000050,

		HOLD		= 0x000100, //Actions
		KICK		= 0x000200,

		ALIVE		= 0x100000,
		DEAD		= 0x200000,
	};

	inline void SetPState(const int& newState)
	{
		pState = (pState | newState);
	}

	inline void PlayerKeyMoves(SDL_KeyboardEvent& key,SDL_MouseButtonEvent& mouse)
	{
		switch(key.type){
		case SDL_KEYDOWN:
			switch(key.keysym.sym){
			case SDLK_w: diry.movul	= 1;		break;
			case SDLK_s: diry.movdr	= 1;		break;
			case SDLK_a: dirx.movul	= 1;		break;
			case SDLK_d: dirx.movdr	= 1;		break;
			case SDLK_LCTRL: Sprinting	= 1;	break;
			case SDLK_RETURN: Center = true;	break;
			default: break;
			} break;
		case SDL_KEYUP:
			switch(key.keysym.sym){
			case SDLK_w: diry.movul	= 0;	 break;
			case SDLK_s: diry.movdr	= 0;	 break;
			case SDLK_a: dirx.movul	= 0;	 break;
			case SDLK_d: dirx.movdr	= 0;	 break;
			case SDLK_LCTRL: Sprinting	= 0; break;
			case SDLK_RETURN: Center = false;	break;
			default: break;
			} break;
		case SDL_MOUSEBUTTONDOWN:	switch(mouse.button){ case SDL_BUTTON_LEFT: MouseC = true; break; default: break; } break;
		case SDL_MOUSEBUTTONUP:		switch(mouse.button){ case SDL_BUTTON_LEFT: MouseC = false; break; default: break; } break;
		default: break;
		}

		#pragma region PlayerMoves
		switch(Sprinting){  case true: Vel = pSpeed(); break; default: Vel = Run(); break; }

		switch(diry.movul){ case true: rndrRect->y -= Vel; break; default: break; }	/* Moved up */
		switch(diry.movdr){ case true: rndrRect->y += Vel; break; default: break; }	/* Moved down */
		switch(dirx.movul){ case true: rndrRect->x -= Vel; break; default: break; }	/* Moved left */
		switch(dirx.movdr){ case true: rndrRect->x += Vel; break; default: break; }	/* Moved right */
		switch(Center){ case true: rndrRect->x = (WIDTH/2),rndrRect->y = (HEIGHT/2); break; default: break; }
		switch(MouseC){ case true: SDL_GetMouseState(&(rndrRect->x),&(rndrRect->y)); break; default: break; }
		#pragma endregion
	}
private:
	Dir dirx, diry;

	bool Sprinting;
	bool Center = false;
	bool MouseC = false;

	int Walk;
	inline int Run()	//Mario's RUNNING speed oscillates (36, 35, 36, 35, 37) --- AVG = 35.8;
	{
		return ((36 + 35 + 36 + 35 + 37)/5);
	}
	inline int pSpeed()	//Mario's SPRINTING speed also oscillates (48, 47, 48, 47, 49) --- AVG = 47.8
	{
		return ((48 + 47 + 48 + 47 + 49)/5);
	}

		

	int Vel;	/* gets converted to int anyway */

	SDL_Texture* s_stand;
	SDL_Texture* s_run0;
	SDL_Texture* s_run1;
protected:
	int pState;
public:
	SDL_Rect* rndrRect;
};