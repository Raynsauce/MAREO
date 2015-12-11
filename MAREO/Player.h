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
class Oscillate {
public:
	Oscillate() : ixrs(new int),ixps(new int) { *ixrs = -1; *ixps = -1; }
	~Oscillate(){	delete ixrs; delete ixps;	}
	
	inline int rrun()
	{
		if(*ixrs <= 0 && brasc == 0){ brasc = !brasc; }
		if(*ixrs >= 5 && brasc == 1){ brasc = !brasc; }
		*ixrs += (brasc ? 1 : -1);

		return rspd[*ixrs];
	}
	inline int prun()
	{
		if(*ixps <= 0 && bpasc == 0){ bpasc = !bpasc; }
		if(*ixps >= 5 && bpasc == 1){ bpasc = !bpasc; }
		*ixps += (bpasc ? 1 : -1);

		return pspd[*ixps];
	}

private:
	int rspd[5] = { 36,35,36,35,37 }; //run spd
	int pspd[5] = { 48,47,48,47,49 };	//P spd
	
	//indexes for arrays
	int *ixrs;
	int *ixps;
	
	bool brasc = 1;	//ixrs is ascending
	bool bpasc = 1;	//ixps is ascending
};

class Player : protected Camera {
public:

	Player() : pRect(new SDL_Rect)
	{
		puts("[INFO] Player object construct");
		*pRect = {(WIDTH/2),(HEIGHT/2)};			//Defined starting position

		dirx = {};
		diry = {};
		
		Vel = Run();
		Sprinting = false;

		s_stand = IMG_LoadTexture(mainrndr,"assets\\mario\\s_stand.png");
		s_run0 = IMG_LoadTexture(mainrndr,"assets\\mario\\s_run0.png");
		s_run1 = IMG_LoadTexture(mainrndr,"assets\\mario\\s_run1.png");
		if( SDL_QueryTexture(s_stand,nullptr,nullptr,&(pRect->w),&(pRect->h)) )	//If QueryTexture failed, print an error
		{ std::cerr << "[ERR] QueryTexture FAILED: " << SDL_GetError() << std::endl; }
		
		//set the value of cProps instead of pointer address
		Camera::cProps->x = pRect->x;
		Camera::cProps->y = pRect->y;
		Camera::cProps->w = WIDTH;
		Camera::cProps->h = HEIGHT;


		SetPState(STAND | ALIVE);

		std::cout << STAND << ", " << ALIVE << std::endl;
		std::cout << "Initial state: " << (STAND|ALIVE) << std::endl;
	}
	~Player()
	{
		puts("[INFO] Player object destruct");
		delete pRect;
		SDL_DestroyTexture(s_stand);
		SDL_DestroyTexture(s_run0);
		SDL_DestroyTexture(s_run1);
	}
	
	inline void Update(SDL_KeyboardEvent& key,SDL_MouseButtonEvent& mouse)
	{
		PlayerKeyMoves(key,mouse);

		SDL_SetRenderDrawColor(mainrndr,255,0,255,255);
		//SDL_RenderDrawRects(mainrndr,pRect,1);
		
		SDL_SetRenderTarget(mainrndr,mainTex);
		SDL_RenderCopy(mainrndr,s_stand,NULL,pRect);
	}

	const enum pState {		//6 types of states -> 6 hex places (?)
		STAND, //Change to better way to change states
		MOVE,
		STOP,
		THING,
		
		WALK, //Movement
		RUN	,
		SPRINT,
		TURN,
		JUMP,
		SWIM,

		HOLD, //Actions
		KICK,

		ALIVE,
		DEAD
	};
	inline void SetPState(const pState& newState){ cState |= (newState); }
	inline pState GetPState(void){	return cState;	}
	

	inline void PlayerKeyMoves(SDL_KeyboardEvent& key,SDL_MouseButtonEvent& mouse)
	{
		switch(key.type){
		case SDL_KEYDOWN:
			switch(key.keysym.sym){
			case SDLK_w: diry.movul	= 1;	 break;
			case SDLK_s: diry.movdr	= 1;	 break;
			case SDLK_a: dirx.movul	= 1;	 break;
			case SDLK_d: dirx.movdr	= 1;	 break;
			case SDLK_LCTRL: Sprinting	= 1; break;
			case SDLK_RETURN: Center  = 1;	 break;
			default: break;
			} break;
		case SDL_KEYUP:
			switch(key.keysym.sym){
			case SDLK_w: diry.movul	= 0;	 break;
			case SDLK_s: diry.movdr	= 0;	 break;
			case SDLK_a: dirx.movul	= 0;	 break;
			case SDLK_d: dirx.movdr	= 0;	 break;
			case SDLK_LCTRL: Sprinting	= 0; break;
			case SDLK_RETURN: Center = 0;	 break;
			default: break;
			} break;
		case SDL_MOUSEBUTTONDOWN:	switch(mouse.button){ case SDL_BUTTON_LEFT: MouseC = true; break; default: break; } break;
		case SDL_MOUSEBUTTONUP:		switch(mouse.button){ case SDL_BUTTON_LEFT: MouseC = false; break; default: break; } break;
		default: break;
		}

		#pragma region PlayerMoves
		switch(Sprinting){  case true: Vel = pSpeed(); break; default: Vel = Run(); break; }

		switch(diry.movul){ case true: pRect->y -= Vel; break; default: break; }	/* Moved up */
		switch(diry.movdr){ case true: pRect->y += Vel; break; default: break; }	/* Moved down */
		switch(dirx.movul){ case true: pRect->x -= Vel; break; default: break; }	/* Moved left */
		switch(dirx.movdr){ case true: pRect->x += Vel; break; default: break; }	/* Moved right */
		switch(Center){ case true: pRect->x = (WIDTH/2),pRect->y = (HEIGHT/2); break; default: break; }
		switch(MouseC){ case true: SDL_GetMouseState(&(pRect->x),&(pRect->y)); break; default: break; }
		#pragma endregion
	}
private:
	Dir dirx, diry;

	bool Sprinting;
	bool Center = false;
	bool MouseC = false;

	Oscillate osc;

	int Walk;
	inline int Run()	{ return osc.rrun(); } //Mario's RUNNING speed oscillates (36, 35, 36, 35, 37) --- AVG = 35.8;
	inline int pSpeed() { return osc.prun(); } //Mario's SPRINTING speed also oscillates (48, 47, 48, 47, 49) --- AVG = 47.8
	int Vel;

	SDL_Texture* s_stand;
	SDL_Texture* s_run0;
	SDL_Texture* s_run1;
protected:
	pState cState;
public:
	SDL_Rect* pRect;
};