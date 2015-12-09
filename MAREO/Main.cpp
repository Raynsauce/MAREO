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

	int otherframe = 0;

	for(; SMW.mEvent->quit.type != SDL_QUIT; SDL_PollEvent(SMW.mEvent))
	{
		//Background updates
		//Enemy updates
		//Item updates
		Mario.Update(SMW.mEvent->key,SMW.mEvent->button);

		#pragma region Frame Update
		SMW.Update();
		#pragma endregion

		//if(otherframe >= 15){ Mario.GetPState(); otherframe = 0; } else { otherframe++;	}
		if((SMW.mEvent->key.type == SDL_KEYDOWN) && (SMW.mEvent->key.keysym.sym == SDLK_ESCAPE)){ SMW.mEvent->quit.type = SDL_QUIT; }
	}

	SDL_Quit();
	return 0;
}

