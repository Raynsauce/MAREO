#include "stdafx.h"
#include "Main.h"
#include "Entities.h"

int main(int argv, char** argc)
{	
	#pragma region SDL_Init
	SDL_SetRenderTarget(mainrndr,mainTex);
	#pragma endregion

	Engine SMW;
	Player Mario;

	for(; SMW.mEvent->quit.type != SDL_QUIT; SDL_PollEvent(SMW.mEvent))
	{
		

		Mario.Update(SMW.mEvent->key,SMW.mEvent->button);
		

		#pragma region Frame Update
		SMW.Update();
		#pragma endregion

		if((SMW.mEvent->key.type == SDL_KEYDOWN) && (SMW.mEvent->key.keysym.sym == SDLK_ESCAPE)){ SMW.mEvent->quit.type = SDL_QUIT; }
	}

	SDL_Quit();
	return 0;
}

