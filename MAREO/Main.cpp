#include "stdafx.h"
#include "Main.h"
#include "Player.h"

int main(int argv, char** argc)
{	
	#pragma region SDL_Init
	*InitSDL;
	SDL_SetRenderTarget(mainrndr,mainTex);
	#pragma endregion

	Engine SMW;
	Player Mario(&SMW);

	Uint8 oframe = 0;

	Uint32 startFrame,endFrame;
	for(; SMW.mEvent->quit.type != SDL_QUIT; SDL_PollEvent(SMW.mEvent))
	{
		startFrame = SDL_GetTicks();
		///Background updates
		///Enemy updates
		///Item updates

		fillEllipse(mainrndr,WIDTH/2,HEIGHT/2,64,64, 128,72,255,255);

		Mario.Update(SMW.mEvent->key,SMW.mEvent->button);

		#pragma region Frame Update
		SMW.Update();
		#pragma endregion

		if((SMW.mEvent->key.type == SDL_KEYDOWN) && (SMW.mEvent->key.keysym.sym == SDLK_ESCAPE)){ SMW.mEvent->quit.type = SDL_QUIT; }
		endFrame = SDL_GetTicks();
	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}