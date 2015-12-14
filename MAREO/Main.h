#pragma once

#define WIDTH 1152
#define HEIGHT 648

inline void InitSDL(){
	std::ios::sync_with_stdio( false );
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0){ std::cerr << "SDL_Init failure! Error: " << SDL_GetError() << std::endl; }
	if(IMG_Init(IMG_INIT_PNG) == 0){ std::cerr << "IMG_Init failure! Error: " << IMG_GetError() << std::endl; }
}

SDL_Window* mainwin		= SDL_CreateWindow("MAREO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_BORDERLESS | SDL_WINDOW_MOUSE_CAPTURE);
SDL_Renderer* mainrndr	= SDL_CreateRenderer(mainwin,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
SDL_Texture* mainTex	= SDL_CreateTexture(mainrndr,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,WIDTH,HEIGHT);