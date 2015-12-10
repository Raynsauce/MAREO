#include "stdafx.h"
#include "Main.h"
#include "Player.h"

int main(int argv, char** argc)
{	
	#pragma region SDL_Init
	SDL_SetRenderTarget(mainrndr,mainTex);
	#pragma endregion

	Engine SMW;
	Player Mario;

	int oframe = 0;

	for(; SMW.mEvent->quit.type != SDL_QUIT; SDL_PollEvent(SMW.mEvent))
	{
		//Background updates
		//Enemy updates
		//Item updates
		Mario.Update(SMW.mEvent->key,SMW.mEvent->button);

		#pragma region Frame Update
		SMW.Update();
		#pragma endregion

		if(oframe >= 30){ std::cout << "Engine State: " << Mario.GetPState()<< "\n\n" 
									<< "Player State: " << SMW.GetEState()	<< "\n"
									<< std::endl; oframe = 0; } else { oframe++; }

		if((SMW.mEvent->key.type == SDL_KEYDOWN) && (SMW.mEvent->key.keysym.sym == SDLK_ESCAPE)){ SMW.mEvent->quit.type = SDL_QUIT; }
	}

	SDL_Quit();
	return 0;
}